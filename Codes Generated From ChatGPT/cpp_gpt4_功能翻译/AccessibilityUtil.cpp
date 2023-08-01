#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

class AccessibilityManager {
public:
    AccessibilityManager() = default;
    void addAccessibilityService(const std::string& serviceId) {
        enabledServices.push_back(serviceId);
    }

    std::vector<std::string> getEnabledAccessibilityServiceList() const {
        return enabledServices;
    }

private:
    std::vector<std::string> enabledServices;
};

class PreviewOverlay {
public:
    float zoomIn(float maxZoom) {
        currentZoom = std::min(currentZoom + 1, maxZoom);
        return currentZoom;
    }

    float zoomOut(float minZoom) {
        currentZoom = std::max(currentZoom - 1, minZoom);
        return currentZoom;
    }

private:
    float currentZoom = 1.0f;
};

class AccessibilityUtil {
public:
    AccessibilityUtil(PreviewOverlay& previewOverlay)
        : mPreviewOverlay(previewOverlay) {
        mZoomPlusButton.onClick = std::bind(&AccessibilityUtil::zoomIn, this);
        mZoomMinusButton.onClick = std::bind(&AccessibilityUtil::zoomOut, this);
    }

    void showZoomUI(float maxZoom) {
        mMaxZoom = maxZoom;
        mZoomPlusButton.setVisible(true);
        mZoomMinusButton.setVisible(true);
        mZoomMinusButton.setEnabled(false);
    }

    void hideZoomUI() {
        mZoomPlusButton.setVisible(false);
        mZoomMinusButton.setVisible(false);
    }

    void setAccessibilityManager(AccessibilityManager* manager) {
        mAccessibilityManager = manager;
    }

    bool isAccessibilityEnabled() {
        return isTouchExplorationEnabled() || containsGoogleAccessibilityService();
    }

private:
    class Button {
    public:
        void setVisible(bool visible) {
            mVisible = visible;
        }

        void setEnabled(bool enabled) {
            mEnabled = enabled;
        }

        std::function<void()> onClick;

    private:
        bool mVisible = false;
        bool mEnabled = true;
    };

    void zoomIn() {
        float currentZoom = mPreviewOverlay.zoomIn(mMaxZoom);

        mZoomMinusButton.setEnabled(true);

        if (currentZoom == mMaxZoom) {
            mZoomPlusButton.setEnabled(false);
        }
    }

    void zoomOut() {
        float currentZoom = mPreviewOverlay.zoomOut(MIN_ZOOM);

        mZoomPlusButton.setEnabled(true);

        if (currentZoom == MIN_ZOOM) {
            mZoomMinusButton.setEnabled(false);
        }
    }

    bool isTouchExplorationEnabled() {
        return mAccessibilityManager->getEnabledAccessibilityServiceList().size() > 0;
    }

    bool containsGoogleAccessibilityService() {
        const auto& enabledServices = mAccessibilityManager->getEnabledAccessibilityServiceList();
        return std::any_of(enabledServices.begin(), enabledServices.end(),
                           [](const std::string& serviceId) {
                               return serviceId.find(ACCESSIBILITY_PACKAGE_NAME_PREFIX) == 0;
                           });
    }

    PreviewOverlay& mPreviewOverlay;
    Button mZoomPlusButton;
    Button mZoomMinusButton;
    float mMaxZoom = 1.0f;
    AccessibilityManager* mAccessibilityManager = nullptr;
    static constexpr float MIN_ZOOM = 1.0f;
    static constexpr const char* ACCESSIBILITY_PACKAGE_NAME_PREFIX = "com.google";
};

int main() {
    PreviewOverlay previewOverlay;
    AccessibilityUtil accessibilityUtil(previewOverlay);

    AccessibilityManager accessibilityManager;
    accessibilityManager.addAccessibilityService("com.google.talkback");
    accessibilityUtil.setAccessibilityManager(&accessibilityManager);

    if (accessibilityUtil.isAccessibilityEnabled()) {
        accessibilityUtil.showZoomUI(5.0f);
    }
    // Perform zoom in and zoom out operations
    accessibilityUtil.hideZoomUI();

    return 0;
}