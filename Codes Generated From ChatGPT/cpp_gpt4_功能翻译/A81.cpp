#include <iostream>
#include <cmath>
#include <atomic>
#include <chrono>
#include <functional>
#include <thread>
#include <memory>

class TimeInterpolator {
public:
    virtual float getInterpolation(float input) = 0;
    virtual ~TimeInterpolator() = default;
};

class P6 {
public:
    class LinearInterpolator : public TimeInterpolator {
    public:
        float getInterpolation(float input) override {
            return input;
        }
    };

    static std::shared_ptr<LinearInterpolator> f8667a;
};

std::shared_ptr<P6::LinearInterpolator> P6::f8667a = std::make_shared<P6::LinearInterpolator>();

class ValueAnimator {
public:
    using AnimatorUpdateListener = std::function<void(ValueAnimator&)>;

    void setFloatValues(float start, float end) {
        start_ = start;
        end_ = end;
    }

    void setDuration(std::chrono::milliseconds duration) {
        duration_ = duration;
    }

    void addUpdateListener(AnimatorUpdateListener listener) {
        listener_ = listener;
    }

    void start() {
        auto start_time = std::chrono::steady_clock::now();
        while (true) {
            auto current_time = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time);
            if (elapsed >= duration_) {
                break;
            }

            float fraction = static_cast<float>(elapsed.count()) / duration_.count();
            fraction = interpolator_->getInterpolation(fraction);

            currentValue_ = start_ + fraction * (end_ - start_);
            if (listener_) {
                listener_(*this);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }
    }

    float getAnimatedFraction() const {
        return (currentValue_ - start_) / (end_ - start_);
    }

    void setInterpolator(std::shared_ptr<TimeInterpolator> interpolator) {
        interpolator_ = interpolator;
    }

private:
    float start_ = 0.0f;
    float end_ = 0.0f;
    float currentValue_ = 0.0f;
    std::chrono::milliseconds duration_{0};
    AnimatorUpdateListener listener_;
    std::shared_ptr<TimeInterpolator> interpolator_ = P6::f8667a;
};

class C81 {
public:
    int O = 0;
    int P = 0;
    int L = 0;
    int M = 0;

    void postInvalidateOnAnimation() {
        std::cout << "Called postInvalidateOnAnimation with L = " << L << " and M = " << M << std::endl;
    }
};

class A81 {
public:
    A81(std::shared_ptr<C81> c81, int i, int i2)
        : H(c81), F(i), G(i2) {
    }

    void onAnimationUpdate(ValueAnimator& valueAnimator) {
        float animatedFraction = valueAnimator.getAnimatedFraction();
        auto c81 = H;
        int i = c81->O;
        int i2 = F;
        auto timeInterpolator = P6::f8667a;
        int round = std::round(static_cast<float>(i2 - i) * animatedFraction) + i;
        int i3 = H->P;
        int round2 = std::round(animatedFraction * static_cast<float>(G - i3)) + i3;
        if (round != c81->L || round2 != c81->M) {
            c81->L = round;
            c81->M = round2;
std::atomic<int> atomicInteger;
c81->postInvalidateOnAnimation();
}
}
void startAnimation() {
    ValueAnimator animator;
    animator.setFloatValues(0.0f, 1.0f);
    animator.setDuration(std::chrono::milliseconds(1000));
    animator.setInterpolator(P6::f8667a);
    animator.addUpdateListener([this](ValueAnimator& valueAnimator) {
        onAnimationUpdate(valueAnimator);
    });
    animator.start();
}
private:
std::shared_ptr<C81> H;
int F;
int G;
};

int main() {
auto c81 = std::make_shared<C81>();
c81->O = 10;
c81->P = 20;
int i = 30;
int i2 = 40;

A81 a81(c81, i, i2);
a81.startAnimation();

return 0;
}
