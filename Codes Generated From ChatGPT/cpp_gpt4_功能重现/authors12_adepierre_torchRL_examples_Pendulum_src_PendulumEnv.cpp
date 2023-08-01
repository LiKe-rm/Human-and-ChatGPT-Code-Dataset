#include <iostream>
#include <cmath>
#include <vector>
#include <random>

class Line {
public:
    Line(double x1, double y1, double x2, double y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}

    double x1, y1, x2, y2;
};

bool LinesCross(const Line& line1, const Line& line2) {
    double denominator = (line1.x1 - line1.x2) * (line2.y1 - line2.y2) - (line1.y1 - line1.y2) * (line2.x1 - line2.x2);

    if (denominator == 0) {
        return false;
    }

    double numerator1 = (line1.y1 - line2.y1) * (line2.x1 - line2.x2) - (line1.x1 - line2.x1) * (line2.y1 - line2.y2);
    double numerator2 = (line1.y1 - line2.y1) * (line1.x1 - line1.x2) - (line1.x1 - line2.x1) * (line1.y1 - line1.y2);

    double r = numerator1 / denominator;
    double s = numerator2 / denominator;

    return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);
}

bool LinesCrossPixel(const Line& line, double x, double y, double pixelSize) {
    Line left(x, y, x, y + pixelSize);
    Line right(x + pixelSize, y, x + pixelSize, y + pixelSize);
    Line top(x, y, x + pixelSize, y);
    Line bottom(x, y + pixelSize, x + pixelSize, y + pixelSize);

    return LinesCross(line, left) || LinesCross(line, right) || LinesCross(line, top) || LinesCross(line, bottom);
}

class PendulumEnv {
public:
    PendulumEnv(double dt) : dt(dt), angle(0), angular_velocity(0) {
        reset();
    }

    void reset() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> angle_dist(-M_PI, M_PI);
        std::uniform_real_distribution<> velocity_dist(-1, 1);

        angle = angle_dist(gen);
        angular_velocity = velocity_dist(gen);
    }

    void draw(double x, double y, double length, double pixelSize) {
        double x2 = x + length * sin(angle);
        double y2 = y - length * cos(angle);

        Line pendulumLine(x, y, x2, y2);

        for (int i = 0; i < 1000; ++i) {
            for (int j = 0; j < 1000; ++j) {
                if (LinesCrossPixel(pendulumLine, i * pixelSize, j * pixelSize, pixelSize)) {
                    std::cout << "*";
                } else {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }
    }

    void step(double action) {
        StepImpl(action);
    }

    double getAngle() const {
        return angle;
    }

    double getAngularVelocity() const {
        return angular_velocity;
    }

private:
    void StepImpl(double action) {
        const double gravity = 9.8;
        const double mass = 1;
        const double length = 1;

        double torque = action;
                double inertia = mass * length * length;
        double angular_acceleration = (torque - mass * gravity * length * sin(angle)) / inertia;

        angular_velocity += angular_acceleration * dt;
        angle += angular_velocity * dt;

        // Normalize the angle to the range [-pi, pi]
        angle = std::fmod(angle, 2 * M_PI);
        if (angle > M_PI) {
            angle -= 2 * M_PI;
        } else if (angle < -M_PI) {
            angle += 2 * M_PI;
        }
    }

    double dt;
    double angle;
    double angular_velocity;
};

int main() {
    PendulumEnv env(0.01);

    for (int i = 0; i < 1000; ++i) {
        double action = 0.0;  // Replace this with the output of your machine learning model
        env.step(action);

        double angle = env.getAngle();
        double angular_velocity = env.getAngularVelocity();
        std::cout << "Step " << i << ", Angle: " << angle << ", Angular Velocity: " << angular_velocity << std::endl;

        // Uncomment the following line to draw the pendulum at each time step
        // env.draw(500, 500, 100, 1);
    }

    return 0;
}

