# ~/livox_ros2_ws/src/lio_livox_ros2/launch/lio_livox.launch.py
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration
from launch.actions import DeclareLaunchArgument
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    pkg_share = get_package_share_directory('lio_livox_ros2')
    
    # パラメータ設定
    config_file = os.path.join(pkg_share, 'config', 'mid360_config.yaml')
    rviz_config = os.path.join(pkg_share, 'rviz', 'lio.rviz')
    pcd_file = os.path.join(pkg_share, 'pcd', 'map.pcd')
    
    # ノード定義
    scan_registration_node = Node(
        package='lio_livox_ros2',
        executable='scan_registration',
        name='scan_registration',
        output='screen',
        parameters=[{
            'config_file': config_file,
            'msg_type': 0
        }]
    )
    
    # Ceres Solverが利用可能な場合のみpose_estimationノードを追加
    try:
        pose_estimation_node = Node(
            package='lio_livox_ros2',
            executable='pose_estimation',
            name='pose_estimation',
            output='screen',
            parameters=[{
                'IMU_Mode': 1,
                'filter_parameter_corner': 0.2,
                'filter_parameter_surf': 0.4,
                'save_map_file': pcd_file
            }]
        )
        
        # RViz2ノード
        rviz_node = Node(
            package='rviz2',
            executable='rviz2',
            name='rviz2',
            arguments=['-d', rviz_config]
        )
        
        return LaunchDescription([
            scan_registration_node,
            pose_estimation_node,
            rviz_node
        ])
        
    except:
        # pose_estimationが利用できない場合は最小構成で起動
        return LaunchDescription([
            scan_registration_node
        ])