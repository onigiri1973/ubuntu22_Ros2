from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        # スタティックTF
        Node(
            package="tf2_ros",
            executable="static_transform_publisher",
            name="base_link_to_lidar",
            arguments=["0", "0", "0", "0", "0", "0", "base_link", "livox_frame"]
        ),
        
        # RTAB-Map（3Dマッピング）
        Node(
            package="rtabmap_ros",
            executable="rtabmap",
            name="rtabmap",
            output="screen",
            parameters=[{
                "subscribe_depth": False,
                "subscribe_rgb": False,
                "subscribe_scan_cloud": True,
                "frame_id": "base_link",
                "approx_sync": True,
                "grid_size": 0.05,
                "queue_size": 10
            }],
            remappings=[
                # 実際のトピック名に合わせて調整
                ("scan_cloud", "/livox/lidar"),
            ]
        )
    ])
