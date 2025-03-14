#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <tf2_ros/tf2_ros/transform_broadcaster.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/registration/icp.h>
#include <pcl_conversions/pcl_conversions.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/slam/PriorFactor.h>
#include <gtsam/slam/BetweenFactor.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/nonlinear/ISAM2.h>
#include <gtsam/nonlinear/Values.h>
#include <gtsam/inference/Symbol.h>

using namespace gtsam;

// Livox用カスタムポイントタイプの定義
struct PointXYZIT {
    PCL_ADD_POINT4D;
    uint8_t intensity;
    double timestamp;
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
} EIGEN_ALIGN16;

POINT_CLOUD_REGISTER_POINT_STRUCT(PointXYZIT,
    (float, x, x)
    (float, y, y)
    (float, z, z)
    (uint8_t, intensity, intensity)
    (double, timestamp, timestamp)
)

class LivoxPoseEstimation : public rclcpp::Node {
public:
    LivoxPoseEstimation() : Node("livox_pose_estimation") {
        // パラメータの初期化
        this->declare_parameter("voxel_leaf_size", 0.2);
        this->declare_parameter("icp_max_correspondence_distance", 0.3);
        this->declare_parameter("icp_max_iterations", 100);
        this->declare_parameter("keyframe_distance_threshold", 0.5);
        
        voxel_leaf_size_ = this->get_parameter("voxel_leaf_size").as_double();
        icp_max_corr_dist_ = this->get_parameter("icp_max_correspondence_distance").as_double();
        icp_max_iter_ = this->get_parameter("icp_max_iterations").as_int();
        keyframe_dist_thresh_ = this->get_parameter("keyframe_distance_threshold").as_double();
        
        // サブスクライバーとパブリッシャーの設定
        cloud_sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
            "/livox/lidar", 10, 
            std::bind(&LivoxPoseEstimation::cloudCallback, this, std::placeholders::_1));
        
        odom_pub_ = this->create_publisher<nav_msgs::msg::Odometry>("/odometry", 10);
        map_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/map", 1);
        
        tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(*this);
        
        // GTSAMの初期化
        graph_ = std::make_shared<NonlinearFactorGraph>();
        initial_estimate_ = std::make_shared<Values>();
        
        // ISAM2の設定
        ISAM2Params isam_params;
        isam_params.relinearizeThreshold = 0.1;
        isam_params.relinearizeSkip = 1;
        isam_ = std::make_shared<ISAM2>(isam_params);
        
        // 初期ポーズのセットアップ
        current_pose_ = gtsam::Pose3::Identity();;
        initial_estimate_->insert(Symbol('x', 0), current_pose_);
        
        // 初期ポーズのプライアファクター
        auto prior_noise = noiseModel::Diagonal::Sigmas(
            (Vector(6) << 0.01, 0.01, 0.01, 0.01, 0.01, 0.01).finished());
        graph_->add(PriorFactor<Pose3>(Symbol('x', 0), current_pose_, prior_noise));
        
        // ISAM2の初期化
        isam_->update(*graph_, *initial_estimate_);
        graph_->resize(0);
        initial_estimate_->clear();
        
        pose_id_ = 1;
        has_first_scan_ = false;
        
        // グローバルマップの初期化
        global_map_ = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud<pcl::PointXYZ>);
        previous_scan_ = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud<pcl::PointXYZ>);
        
        RCLCPP_INFO(this->get_logger(), "Livox Pose Estimation initialized with:");
        RCLCPP_INFO(this->get_logger(), "  Voxel leaf size: %.2f", voxel_leaf_size_);
        RCLCPP_INFO(this->get_logger(), "  ICP max correspondence distance: %.2f", icp_max_corr_dist_);
        RCLCPP_INFO(this->get_logger(), "  ICP max iterations: %d", icp_max_iter_);
        RCLCPP_INFO(this->get_logger(), "  Keyframe distance threshold: %.2f", keyframe_dist_thresh_);
    }

private:
    void cloudCallback(const sensor_msgs::msg::PointCloud2::SharedPtr msg) {
        // PCL点群に変換
        pcl::PointCloud<pcl::PointXYZ>::Ptr raw_cloud(new pcl::PointCloud<pcl::PointXYZ>);
        pcl::fromROSMsg(*msg, *raw_cloud);
        
        // ダウンサンプリング
        pcl::PointCloud<pcl::PointXYZ>::Ptr filtered_cloud(new pcl::PointCloud<pcl::PointXYZ>);
        pcl::VoxelGrid<pcl::PointXYZ> voxel_filter;
        voxel_filter.setInputCloud(raw_cloud);
        voxel_filter.setLeafSize(voxel_leaf_size_, voxel_leaf_size_, voxel_leaf_size_);
        voxel_filter.filter(*filtered_cloud);
        
        // 初回スキャンの場合
        if (!has_first_scan_) {
            *previous_scan_ = *filtered_cloud;
            *global_map_ += *filtered_cloud;
            has_first_scan_ = true;
            
            // 初期マップの公開
            publishMap();
            return;
        }
        
        // ICPを使用して前回のスキャンと現在のスキャンを位置合わせ
        pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
        icp.setInputSource(filtered_cloud);
        icp.setInputTarget(previous_scan_);
        icp.setMaxCorrespondenceDistance(icp_max_corr_dist_);
        icp.setMaximumIterations(icp_max_iter_);
        
        pcl::PointCloud<pcl::PointXYZ> aligned_cloud;
        icp.align(aligned_cloud);
        
        if (!icp.hasConverged()) {
            RCLCPP_WARN(this->get_logger(), "ICP did not converge, skipping frame");
            return;
        }
        
        // ICPで求めた変換行列
        Eigen::Matrix4f icp_transform = icp.getFinalTransformation();
        
        // Eigen::Matrix4f to gtsam::Pose3
        Eigen::Matrix3f rotation = icp_transform.block<3, 3>(0, 0);
        Eigen::Vector3f translation = icp_transform.block<3, 1>(0, 3);
        
        gtsam::Rot3 rot(
            rotation(0, 0), rotation(0, 1), rotation(0, 2),
            rotation(1, 0), rotation(1, 1), rotation(1, 2),
            rotation(2, 0), rotation(2, 1), rotation(2, 2)
        );
        gtsam::Point3 trans(translation(0), translation(1), translation(2));
        
        // 前回のポーズからの相対変換
        gtsam::Pose3 relative_pose(rot, trans);
        
        // GTSAMファクターグラフの更新
        auto odometry_noise = noiseModel::Diagonal::Sigmas(
            (Vector(6) << 0.1, 0.1, 0.1, 0.1, 0.1, 0.1).finished());
        
        graph_->add(BetweenFactor<Pose3>(
            Symbol('x', pose_id_ - 1), Symbol('x', pose_id_), relative_pose, odometry_noise));
        
        // 現在のポーズを推定
        gtsam::Pose3 predicted_pose = current_pose_.compose(relative_pose);
        initial_estimate_->insert(Symbol('x', pose_id_), predicted_pose);
        
        // ISAM2の更新
        isam_->update(*graph_, *initial_estimate_);
        Values current_estimate = isam_->calculateEstimate();
        current_pose_ = current_estimate.at<Pose3>(Symbol('x', pose_id_));
        
        // グラフとイニシャル推定値をクリア
        graph_->resize(0);
        initial_estimate_->clear();
        
        // キーフレーム判定 - 一定距離以上移動した場合
        double distance_moved = (current_pose_.translation() - last_keyframe_pose_.translation()).norm();
        
        if (distance_moved > keyframe_dist_thresh_) {
            // キーフレームとして保存
            *previous_scan_ = *filtered_cloud;
            last_keyframe_pose_ = current_pose_;
            
            // グローバルマップに追加
            pcl::PointCloud<pcl::PointXYZ>::Ptr transformed_cloud(new pcl::PointCloud<pcl::PointXYZ>);
            pcl::transformPointCloud(*filtered_cloud, *transformed_cloud, current_pose_.matrix());
            *global_map_ += *transformed_cloud;
            
            // ダウンサンプリングしてマップのサイズを管理
            if (global_map_->size() > 100000) { // 任意のしきい値
                pcl::VoxelGrid<pcl::PointXYZ> map_filter;
                map_filter.setInputCloud(global_map_);
                map_filter.setLeafSize(voxel_leaf_size_, voxel_leaf_size_, voxel_leaf_size_);
                map_filter.filter(*global_map_);
            }
            
            // マップを公開
            publishMap();
        }
        
        // オドメトリの公開
        publishOdometry(msg->header.stamp);
        
        // 次のフレームのためのIDインクリメント
        pose_id_++;
    }
    
    void publishOdometry(const rclcpp::Time& stamp) {
        // オドメトリメッセージの生成
        nav_msgs::msg::Odometry odom_msg;
        odom_msg.header.stamp = stamp;
        odom_msg.header.frame_id = "odom";
        odom_msg.child_frame_id = "base_link";
        
        // Pose3からPose情報を抽出
        gtsam::Point3 position = current_pose_.translation();
        gtsam::Quaternion quat = current_pose_.rotation().toQuaternion();
        
        odom_msg.pose.pose.position.x = position.x();
        odom_msg.pose.pose.position.y = position.y();
        odom_msg.pose.pose.position.z = position.z();
        odom_msg.pose.pose.orientation.w = quat.w();
        odom_msg.pose.pose.orientation.x = quat.x();
        odom_msg.pose.pose.orientation.y = quat.y();
        odom_msg.pose.pose.orientation.z = quat.z();
        
        // 共分散（簡易的な設定）
        for (int i = 0; i < 36; i++) {
            odom_msg.pose.covariance[i] = (i % 7 == 0) ? 0.01 : 0.0;
        }
        
        odom_pub_->publish(odom_msg);
        
        // TF情報の公開
        geometry_msgs::msg::TransformStamped transform_stamped;
        transform_stamped.header.stamp = stamp;
        transform_stamped.header.frame_id = "odom";
        transform_stamped.child_frame_id = "base_link";
        
        transform_stamped.transform.translation.x = position.x();
        transform_stamped.transform.translation.y = position.y();
        transform_stamped.transform.translation.z = position.z();
        transform_stamped.transform.rotation.w = quat.w();
        transform_stamped.transform.rotation.x = quat.x();
        transform_stamped.transform.rotation.y = quat.y();
        transform_stamped.transform.rotation.z = quat.z();
        
        tf_broadcaster_->sendTransform(transform_stamped);
    }
    
    void publishMap() {
        sensor_msgs::msg::PointCloud2 map_msg;
        pcl::toROSMsg(*global_map_, map_msg);
        map_msg.header.stamp = this->now();
        map_msg.header.frame_id = "odom";
        map_pub_->publish(map_msg);
    }
    
    // サブスクライバーとパブリッシャー
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr cloud_sub_;
    rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr odom_pub_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr map_pub_;
    std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
    
    // GTSAMの変数
    std::shared_ptr<NonlinearFactorGraph> graph_;
    std::shared_ptr<Values> initial_estimate_;
    std::shared_ptr<ISAM2> isam_;
    
    // ポーズ関連
    gtsam::Pose3 current_pose_;
    gtsam::Pose3 last_keyframe_pose_;
    int pose_id_;
    
    // 点群データ
    pcl::PointCloud<pcl::PointXYZ>::Ptr global_map_;
    pcl::PointCloud<pcl::PointXYZ>::Ptr previous_scan_;
    bool has_first_scan_;
    
    // パラメータ
    double voxel_leaf_size_;
    double icp_max_corr_dist_;
    int icp_max_iter_;
    double keyframe_dist_thresh_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<LivoxPoseEstimation>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}