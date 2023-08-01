#include <iostream>

// PID参数结构体
struct PidParameters {
    double Kp;   // 比例控制器参数
    double Ki;   // 积分控制器参数
    double Kd;   // 微分控制器参数
    double iMax; // 积分限幅
};

class PidController {
public:
    // 构造函数
    PidController(PidParameters params, double setPoint, double feedback) :
        m_params(params),
        m_setPoint(setPoint),
        m_feedback(feedback),
        m_integral(0.0),
        m_prevError(0.0) {}

    // 更新PID控制器的目标状态值
    void updateSetPoint(double setPoint) {
        m_setPoint = setPoint;
    }

    // 更新PID控制器的反馈值
    void updateFeedback(double feedback) {
        m_feedback = feedback;
    }

    // 获取PID控制器的控制信号
    double getControlSignal() {
        // 计算误差
        double error = m_setPoint - m_feedback;

        // 计算PID控制器的三个部分
        double p = m_params.Kp * error;
        double i = updateIntegral(error);
        double d = m_params.Kd * (error - m_prevError);

        // 更新前一个误差值
        m_prevError = error;

        // 计算控制信号
        double controlSignal = p + i + d;

        return controlSignal;
    }

private:
    PidParameters m_params; // PID参数
    double m_setPoint;      // 目标状态值
    double m_feedback;      // 反馈值
    double m_integral;      // 积分值
    double m_prevError;     // 上一个误差值

    // 更新积分值，并进行积分限幅
    double updateIntegral(double error) {
        m_integral += error;
        if (m_integral > m_params.iMax) {
            m_integral = m_params.iMax;
        }
        else if (m_integral < -m_params.iMax) {
            m_integral = -m_params.iMax;
        }
        double integral = m_params.Ki * m_integral;

        return integral;
    }
};

int main() {
    // 初始化PID参数
    PidParameters params;
    params.Kp = 1.0;
    params.Ki = 0.5;
    params.Kd = 0.1;
    params.iMax = 10.0;

    // 初始化PID控制器
    PidController pid(params, 10.0, 0.0);

    // 模拟PID控制器
    for (int i = 0; i < 100; i++) {
        // 更新反馈值
        double feedback = i * 0.1;

        // 获取控制信号
        double controlSignal = pid.getControlSignal();

        // 输出结果
        std::cout << "Feedback: " << feedback << ", Control Signal: " << controlSignal << std::endl;

        // 更新PID控制器的反馈值
        pid.updateFeedback(feedback);
    }

    return 0;
}
