#include <rclcpp/rclcpp.hpp> // ROS2用のヘッダー
#include <sensor_msgs/msg/point_cloud2.hpp> // ROS2の命名規則に合わせる
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>

class ScanRegistrationNode : public rclcpp::Node
{
public:
  ScanRegistrationNode() : Node("scan_registration")
  {
    // パラメータの宣言と取得
    this->declare_parameter("config_file", "config/mid360_config.yaml");
    this->declare_parameter("msg_type", 0);
    
    // パラメータの読み取り
    std::string config_file;
    this->get_parameter("config_file", config_file);
    int msg_type;
    this->get_parameter("msg_type", msg_type);
    
    RCLCPP_INFO(this->get_logger(), "Configuration file: %s", config_file.c_str());
    RCLCPP_INFO(this->get_logger(), "Message type: %d", msg_type);
    
    // パブリッシャーの作成
    corner_points_publisher_ = this->create_publisher<sensor_msgs::msg::PointCloud2>(
      "livox/corner_points", 10);
    surface_points_publisher_ = this->create_publisher<sensor_msgs::msg::PointCloud2>(
      "livox/surface_points", 10);
    
    // サブスクライバーの作成
    point_cloud_subscriber_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
      "livox/lidar", 10, std::bind(&ScanRegistrationNode::pointCloudCallback, this, std::placeholders::_1));
    
    RCLCPP_INFO(this->get_logger(), "Scan Registration Node initialized.");
  }

private:
  void pointCloudCallback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
  {
    // PCL点群に変換
    pcl::PointCloud<pcl::PointXYZI>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZI>());
    pcl::fromROSMsg(*msg, *cloud);
    
    RCLCPP_INFO_ONCE(this->get_logger(), "Received first point cloud with %zu points", cloud->size());
    
    // 特徴点の抽出（実際のLIO-Livoxアルゴリズムに置き換え）
    pcl::PointCloud<pcl::PointXYZI>::Ptr corner_points(new pcl::PointCloud<pcl::PointXYZI>());
    pcl::PointCloud<pcl::PointXYZI>::Ptr surface_points(new pcl::PointCloud<pcl::PointXYZI>());
    
    // TODO: 特徴点抽出処理を実装
    
    // ROS2メッセージに変換して発行
    sensor_msgs::msg::PointCloud2 corner_msg;
    pcl::toROSMsg(*corner_points, corner_msg);
    corner_msg.header = msg->header;
    corner_points_publisher_->publish(corner_msg);
    
    sensor_msgs::msg::PointCloud2 surface_msg;
    pcl::toROSMsg(*surface_points, surface_msg);
    surface_msg.header = msg->header;
    surface_points_publisher_->publish(surface_msg);
  }

  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr corner_points_publisher_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr surface_points_publisher_;
  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr point_cloud_subscriber_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ScanRegistrationNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}