#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <cstdlib>
#include <ctime>

class TurtleRunner : public rclcpp::Node
{
public:
    TurtleRunner() : Node("turtle_runner")
    {
        // 控制乌龟2的速度
        velocity_publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle2/cmd_vel", 10);

        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(500),
            std::bind(&TurtleRunner::run_away, this));

        std::srand(std::time(nullptr));  // 随机数种子
    }

private:
    void run_away()
    {
        auto twist_msg = geometry_msgs::msg::Twist();
        
        // 随机生成线速度和角速度
        twist_msg.linear.x = 2.0;
        twist_msg.angular.z = (std::rand() % 10 - 5) * 0.1;  // 随机转向

        velocity_publisher_->publish(twist_msg);
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr velocity_publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleRunner>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
