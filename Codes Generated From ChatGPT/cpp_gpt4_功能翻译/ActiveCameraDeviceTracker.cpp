#include <iostream>
#include <memory>
#include <mutex>
#include <string>

class CameraId {
public:
    explicit CameraId(const std::string& id)
        : mId(id) {}

    const std::string& getId() const {
        return mId;
    }

    bool operator==(const CameraId& other) const {
        return mId == other.mId;
    }

private:
    std::string mId;
};

class ActiveCameraDeviceTracker {
public:
    static ActiveCameraDeviceTracker& instance() {
        static ActiveCameraDeviceTracker instance;
        return instance;
    }

    std::shared_ptr<CameraId> getActiveCamera() {
        std::lock_guard<std::mutex> lock(mLock);
        return mActiveCamera;
    }

    std::shared_ptr<CameraId> getActiveOrPreviousCamera() {
        std::lock_guard<std::mutex> lock(mLock);
        if (mActiveCamera) {
            return mActiveCamera;
        }
        std::cout << "Returning previously active camera: " << mPreviousCamera->getId() << std::endl;
        return mPreviousCamera;
    }

    void onCameraOpening(const std::shared_ptr<CameraId>& key) {
        std::lock_guard<std::mutex> lock(mLock);
        if (mActiveCamera && *mActiveCamera != *key) {
            mPreviousCamera = mActiveCamera;
        }

        std::cout << "Tracking active camera: " << mActiveCamera->getId() << std::endl;
        mActiveCamera = key;
    }

    void onCameraClosed(const std::shared_ptr<CameraId>& key) {
        std::lock_guard<std::mutex> lock(mLock);
        if (mActiveCamera && *mActiveCamera == *key) {
            mPreviousCamera = mActiveCamera;
            mActiveCamera = nullptr;
        }
    }

private:
    ActiveCameraDeviceTracker() = default;

    std::mutex mLock;
    std::shared_ptr<CameraId> mActiveCamera;
    std::shared_ptr<CameraId> mPreviousCamera;
};

int main() {
    auto tracker = ActiveCameraDeviceTracker::instance();
    auto camera1 = std::make_shared<CameraId>("Camera1");
    auto camera2 = std::make_shared<CameraId>("Camera2");

    tracker.onCameraOpening(camera1);
    tracker.onCameraClosed(camera1);
    tracker.onCameraOpening(camera2);

    auto activeCamera = tracker.getActiveCamera();
    if (activeCamera) {
        std::cout << "Active camera: " << activeCamera->getId() << std::endl;
    } else {
        std::cout << "No active camera" << std::endl;
    }

    auto activeOrPreviousCamera = tracker.getActiveOrPreviousCamera();
    if (activeOrPreviousCamera) {
        std::cout << "Active or previous camera: " << activeOrPreviousCamera->getId() << std::endl;
    } else {
        std::cout << "No active or previous camera" << std::endl;
    }

    return 0;
}
