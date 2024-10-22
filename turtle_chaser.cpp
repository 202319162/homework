#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/msg/pose.hpp"
#include <cmath>

class TurtleChaser : public rclcpp::Node
{
public:
    TurtleChaser() : Node("turtle_chaser")
    {
        // 订阅乌龟2的位置
        turtle2_pose_subscriber_ = this->create_subscription<turtlesim::msg::Pose>(
            "/turtle2/pose", 10, std::bind(&TurtleChaser::chase_callback, this, std::placeholders::_1));
        
        // 订阅乌龟1的位置
        turtle1_pose_subscriber_ = this->create_subscription<turtlesim::msg::Pose>(
            "/turtle1/pose", 10, std::bind(&TurtleChaser::pose_callback, this, std::placeholders::_1));
        
        // 控制乌龟1的速度
        velocity_publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);

        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(100),
            std::bind(&TurtleChaser::chase_turtle, this));
    }

private:
    // 直接将共享指针赋值，而不是解引用
    void pose_callback(const turtlesim::msg::Pose::SharedPtr msg)
    {
        turtle1_pose_ = msg;  // 直接赋值共享指针
    }

    void chase_callback(const turtlesim::msg::Pose::SharedPtr msg)
    {
        turtle2_pose_ = msg;  // 直接赋值共享指针
    }

    void chase_turtle()
    {
        if (!turtle2_pose_ || !turtle1_pose_)
        {
            return;
        }

        auto twist_msg = geometry_msgs::msg::Twist();
        
        // 计算乌龟1到乌龟2的角度
        double angle_to_turtle2 = atan2(turtle2_pose_->y - turtle1_pose_->y,
                                        turtle2_pose_->x - turtle1_pose_->x);

        // 设置线速度和角速度，让乌龟1向乌龟2移动
        twist_msg.linear.x = 2.0;
        twist_msg.angular.z = 4.0 * (angle_to_turtle2 - turtle1_pose_->theta);

        velocity_publisher_->publish(twist_msg);
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr velocity_publisher_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr turtle2_pose_subscriber_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr turtle1_pose_subscriber_;
    rclcpp::TimerBase::SharedPtr timer_;
    turtlesim::msg::Pose::SharedPtr turtle1_pose_;
    turtlesim::msg::Pose::SharedPtr turtle2_pose_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleChaser>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
