#include <string>
#include <ctime>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <filesystem>

class OneCamera {
public:
    virtual void setFocusStateListener() = 0;
    virtual void setFocusDistanceListener() = 0;
    virtual void setReadyStateChangedListener() = 0;
    virtual float getMaxZoom() = 0;
    virtual void setZoom(float zoom) = 0;
};

class FocusStateListener {};
class ReadyStateChangedListener {};
class FocusDistanceListener {};

class AbstractOneCamera : public OneCamera {
protected:
    std::shared_ptr<FocusStateListener> mFocusStateListener;
    std::shared_ptr<ReadyStateChangedListener> mReadyStateChangedListener;
    std::shared_ptr<FocusDistanceListener> mFocusDistanceListener;

    static constexpr int DEBUG_FOLDER_SERIAL_LENGTH = 4;

public:
    void setFocusStateListener() override {
        mFocusStateListener = std::make_shared<FocusStateListener>();
    }

    void setFocusDistanceListener() override {
        mFocusDistanceListener = std::make_shared<FocusDistanceListener>();
    }

    void setReadyStateChangedListener() override {
        mReadyStateChangedListener = std::make_shared<ReadyStateChangedListener>();
    }

    static std::string makeDebugDir(const std::filesystem::path& root, const std::string& folderName) {
        if (!std::filesystem::exists(root) || !std::filesystem::is_directory(root)) {
            throw std::runtime_error("Gcam debug directory not valid or doesn't exist: " + root.string());
        }

        std::string serialSubstring = "1234"; // Replace with a method to get the device serial number substring

        std::time_t t = std::time(nullptr);
        std::tm tm = *std::localtime(&t);
        std::stringstream ss;
        ss << std::put_time(&tm, "%Y%m%d_%H%M%S");

        std::string burstFolderName = serialSubstring + "_" + ss.str();
        std::filesystem::path destFolder = root / folderName / burstFolderName;

        if (!std::filesystem::create_directories(destFolder)) {
            throw std::runtime_error("Could not create Gcam debug data folder.");
        }

        return destFolder.string();
    }

    void broadcastReadyState(bool readyForCapture) {
        if (mReadyStateChangedListener) {
            // Call a method in the listener class to notify the state change
        }
    }

    float getMaxZoom() override {
        return 1.0f;
    }

    void setZoom(float zoom) override {
        // No-op
    }
};

int main() {
    AbstractOneCamera camera;

    std::string debugDir = AbstractOneCamera::makeDebugDir("root_folder", "sub_folder");
    std::cout << "Debug directory: " << debugDir << std::endl;

    return 0;
}
