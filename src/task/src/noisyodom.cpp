#include <rclcpp/rclcpp.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <random>

class NoisyOdometryNode : public rclcpp::Node
{
public:
  NoisyOdometryNode() : Node("noisy_odometry_node")
  {
    odom_subscriber_ = this->create_subscription<nav_msgs::msg::Odometry>(
        "/odom", 10, std::bind(&NoisyOdometryNode::odom_callback, this, std::placeholders::_1));
    noisy_odom_publisher_ = this->create_publisher<nav_msgs::msg::Odometry>("/noisy_odom", 10);

    tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);

    std::random_device rd;
    rng_ = std::mt19937(rd());
    noise_dist_ = std::normal_distribution<>(0.0, 0.08); // Mean 0, standard deviation 0.08
  }

private:
  void odom_callback(const nav_msgs::msg::Odometry::SharedPtr msg)
  {
    // Creating a new Odometry message and adding noise
    auto noisy_odom = *msg;

    noisy_odom.pose.pose.position.x += noise_dist_(rng_);
    noisy_odom.pose.pose.position.y += noise_dist_(rng_);
    noisy_odom.pose.pose.position.z += noise_dist_(rng_);
    noisy_odom.pose.pose.orientation.x += noise_dist_(rng_);
    noisy_odom.pose.pose.orientation.y += noise_dist_(rng_);
    noisy_odom.pose.pose.orientation.z += noise_dist_(rng_);
    noisy_odom.pose.pose.orientation.w += noise_dist_(rng_);

    noisy_odom.twist.twist.linear.x += noise_dist_(rng_);
    noisy_odom.twist.twist.linear.y += noise_dist_(rng_);
    noisy_odom.twist.twist.linear.z += noise_dist_(rng_);
    noisy_odom.twist.twist.angular.x += noise_dist_(rng_);
    noisy_odom.twist.twist.angular.y += noise_dist_(rng_);
    noisy_odom.twist.twist.angular.z += noise_dist_(rng_);

    // Publishing the noisy odometry
    noisy_odom_publisher_->publish(noisy_odom);

    // Creating and broadcasting the transform
    geometry_msgs::msg::TransformStamped transform_stamped;

    transform_stamped.header.stamp = noisy_odom.header.stamp;
    transform_stamped.header.frame_id = noisy_odom.header.frame_id;
    transform_stamped.child_frame_id = noisy_odom.child_frame_id;

    transform_stamped.transform.translation.x = noisy_odom.pose.pose.position.x;
    transform_stamped.transform.translation.y = noisy_odom.pose.pose.position.y;
    transform_stamped.transform.translation.z = noisy_odom.pose.pose.position.z;
    transform_stamped.transform.rotation = noisy_odom.pose.pose.orientation;

    tf_broadcaster_->sendTransform(transform_stamped);
  }

  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_subscriber_;
  rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr noisy_odom_publisher_;
  std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
  std::mt19937 rng_;
  std::normal_distribution<> noise_dist_;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<NoisyOdometryNode>());
  rclcpp::shutdown();
  return 0;
}
