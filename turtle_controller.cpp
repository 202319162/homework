#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <chrono>

class TurtleController : public rclcpp::Node
{
public:
    TurtleController() : Node("turtle_controller"), state_(0), move_time_(2.0), turn_time_(1.57)
    {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(100),
            std::bind(&TurtleController::move_square, this));
    }

private:
    void move_square()
    {
        auto message = geometry_msgs::msg::Twist();
        if (state_ == 0)  // 直线运动
        {
            message.linear.x = 2.0;  // 直线速度
            move_time_ -= 0.1;       // 移动一定时间后停止
            if (move_time_ <= 0)
            {
                state_ = 1;  // 切换到转弯状态
                move_time_ = 2.0;  // 重置直线运动时间
            }
        }
        else if (state_ == 1)  // 转弯
        {
            message.angular.z = 1.57;  // 90度旋转（角速度）
            turn_time_ -= 0.1;  // 旋转一定时间后停止
            if (turn_time_ <= 0)
            {
                state_ = 0;  // 切换回直线运动状态
                turn_time_ = 1.57;  // 重置旋转时间
            }
        }
        publisher_->publish(message);  // 发布消息控制海龟
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    int state_;       // 状态机：0为直线，1为旋转
    double move_time_;  // 直线运动时间
    double turn_time_;  // 转弯时间
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleController>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
