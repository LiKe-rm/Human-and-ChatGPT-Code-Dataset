#include <iostream>
#include <functional>
#include <memory>

class CloseListener {
public:
    virtual void onTutorialClosed() = 0;
};

class ViewGroup {
public:
    virtual void removeAllViews() = 0;
    virtual void setVisibility(bool visible) = 0;
};

class LayoutInflater {};
class View {};

class AbstractTutorialOverlay {
public:
    using CloseListenerPtr = std::shared_ptr<CloseListener>;
    using ViewGroupPtr = std::shared_ptr<ViewGroup>;
    using LayoutInflaterPtr = std::shared_ptr<LayoutInflater>;

private:
    int mLayoutResId;
    CloseListenerPtr mCloseListener;
    ViewGroupPtr mPlaceholderWrapper;

public:
    AbstractTutorialOverlay(int layoutResId, CloseListenerPtr closeListener)
        : mLayoutResId(layoutResId), mCloseListener(closeListener) {}

    void show(ViewGroupPtr placeHolderWrapper, LayoutInflaterPtr inflater) {
        mPlaceholderWrapper = placeHolderWrapper;
        if (mPlaceholderWrapper) {
            mPlaceholderWrapper->removeAllViews();
        }

        mPlaceholderWrapper->setVisibility(true);

        // In the real implementation, inflate the layout and call onInflated with the created view.
        // For the sake of simplicity, we'll pass a nullptr here.
        onInflated(nullptr);
    }

protected:
    virtual void onInflated(std::shared_ptr<View> view) = 0;

public:
    void removeOverlayAndHideWrapper() {
        if (mPlaceholderWrapper) {
            mPlaceholderWrapper->removeAllViews();
        }
        mPlaceholderWrapper->setVisibility(false);
    }

    void close() {
        removeOverlayAndHideWrapper();
        if (mCloseListener) {
            mCloseListener->onTutorialClosed();
        }
    }
};

class CustomTutorialOverlay : public AbstractTutorialOverlay {
public:
    CustomTutorialOverlay(int layoutResId, CloseListenerPtr closeListener)
        : AbstractTutorialOverlay(layoutResId, closeListener) {}

protected:
    void onInflated(std::shared_ptr<View> view) override {
        std::cout << "Custom tutorial view inflated" << std::endl;
    }
};

class CustomCloseListener : public CloseListener {
public:
    void onTutorialClosed() override {
        std::cout << "Tutorial closed" << std::endl;
    }
};

class CustomViewGroup : public ViewGroup {
public:
    void removeAllViews() override {
        std::cout << "Removing all views" << std::endl;
    }

    void setVisibility(bool visible) override {
        std::cout << "Setting visibility: " << (visible ? "Visible" : "Gone") << std::endl;
    }
};

int main() {
    auto closeListener = std::make_shared<CustomCloseListener>();
    auto tutorialOverlay = std::make_shared<CustomTutorialOverlay>(1, closeListener);
    auto viewGroup = std::make_shared<CustomViewGroup>();
    auto layoutInflater = std::make_shared<LayoutInflater>();

    tutorialOverlay->show(viewGroup, layoutInflater);
    tutorialOverlay->close();

    return 0;
}
