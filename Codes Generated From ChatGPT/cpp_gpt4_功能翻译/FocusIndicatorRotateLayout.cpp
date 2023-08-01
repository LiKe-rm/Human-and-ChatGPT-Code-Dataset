#include <iostream>
#include <functional>
#include <thread>
#include <chrono>

enum class FocusState {
    IDLE,
    FOCUSING,
    FINISHING
};

class FocusIndicatorRotateLayout {
private:
    FocusState mState = FocusState::IDLE;
    static constexpr int SCALING_UP_TIME = 1000;
    static constexpr int SCALING_DOWN_TIME = 200;
    static constexpr int DISAPPEAR_TIMEOUT = 200;
    std::string mCurrentDrawable;

    std::function<void()> mDisappear = [this] { 
        mCurrentDrawable.clear();
        mState = FocusState::IDLE;
    };

    std::function<void()> mEndAction = [this] { 
        std::this_thread::sleep_for(std::chrono::milliseconds(DISAPPEAR_TIMEOUT));
        mDisappear();
    };

    void setDrawable(const std::string& resid) {
        mCurrentDrawable = resid;
        // Replace this with the actual code to set the drawable.
        std::cout << "Setting drawable: " << resid << std::endl;
    }

    void animate(float scaleX, float scaleY, int duration, bool withEndAction = false) {
        // Replace this with the actual code to perform the animation.
        std::cout << "Animating with scale X: " << scaleX << ", scale Y: " << scaleY 
                  << ", duration: " << duration << std::endl;
        if (withEndAction) {
            mEndAction();
        }
    }

public:
    void showStart() {
        if (mState == FocusState::IDLE) {
            setDrawable("ic_focus_focusing");
            animate(1.5f, 1.5f, SCALING_UP_TIME);
            mState = FocusState::FOCUSING;
        }
    }

    void showSuccess(bool timeout) {
        if (mState == FocusState::FOCUSING) {
            setDrawable("ic_focus_focused");
            animate(1.0f, 1.0f, SCALING_DOWN_TIME, timeout);
            mState = FocusState::FINISHING;
        }
    }

    void showFail(bool timeout) {
        if (mState == FocusState::FOCUSING) {
            setDrawable("ic_focus_failed");
            animate(1.0f, 1.0f, SCALING_DOWN_TIME, timeout);
            mState = FocusState::FINISHING;
        }
    }

    void clear() {
        // Since there's no exact equivalent of "animate().cancel()" in C++, this is skipped.
        mDisappear();
    }

    bool isFocusing() {
        return mState != FocusState::IDLE;
    }
};

int main() {
    FocusIndicatorRotateLayout layout;
    layout.showStart();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    layout.showSuccess(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    layout.clear();
    return 0;
}
