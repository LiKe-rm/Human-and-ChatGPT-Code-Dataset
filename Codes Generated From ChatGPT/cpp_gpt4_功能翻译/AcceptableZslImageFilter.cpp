#include <iostream>
#include <functional>
#include <memory>

class TotalCaptureResultProxy {
public:
    enum LensState { LENS_STATE_STATIONARY };
    enum AEState {
        CONTROL_AE_STATE_INACTIVE,
        CONTROL_AE_STATE_LOCKED,
        CONTROL_AE_STATE_CONVERGED
    };
    enum AFState {
        CONTROL_AF_STATE_INACTIVE,
        CONTROL_AF_STATE_FOCUSED_LOCKED,
        CONTROL_AF_STATE_NOT_FOCUSED_LOCKED,
        CONTROL_AF_STATE_PASSIVE_FOCUSED,
        CONTROL_AF_STATE_PASSIVE_UNFOCUSED
    };

    virtual int get(LensState key) const = 0;
    virtual int get(AEState key) const = 0;
    virtual int get(AFState key) const = 0;
};

class AcceptableZslImageFilter {
private:
    bool requireAFConvergence;
    bool requireAEConvergence;

public:
    AcceptableZslImageFilter(bool requireAFConvergence, bool requireAEConvergence)
        : requireAFConvergence(requireAFConvergence), requireAEConvergence(requireAEConvergence) {}

    bool apply(std::shared_ptr<TotalCaptureResultProxy> metadata) {
        bool result = true;
        result &= isLensStationary(metadata);
        if (requireAFConvergence) {
            result &= isAFAcceptable(metadata);
        }
        if (requireAEConvergence) {
            result &= isAEAcceptable(metadata);
        }
        return result;
    }

private:
    bool isLensStationary(std::shared_ptr<TotalCaptureResultProxy> metadata) {
        int lensState = metadata->get(TotalCaptureResultProxy::LENS_STATE_STATIONARY);
        return lensState == TotalCaptureResultProxy::LENS_STATE_STATIONARY;
    }

    bool isAEAcceptable(std::shared_ptr<TotalCaptureResultProxy> metadata) {
        int aeState = metadata->get(TotalCaptureResultProxy::CONTROL_AE_STATE_INACTIVE);
        switch (aeState) {
            case TotalCaptureResultProxy::CONTROL_AE_STATE_INACTIVE:
            case TotalCaptureResultProxy::CONTROL_AE_STATE_LOCKED:
            case TotalCaptureResultProxy::CONTROL_AE_STATE_CONVERGED:
                return true;
            default:
                return false;
        }
    }

    bool isAFAcceptable(std::shared_ptr<TotalCaptureResultProxy> metadata) {
        int afState = metadata->get(TotalCaptureResultProxy::CONTROL_AF_STATE_INACTIVE);
        switch (afState) {
            case TotalCaptureResultProxy::CONTROL_AF_STATE_INACTIVE:
            case TotalCaptureResultProxy::CONTROL_AF_STATE_FOCUSED_LOCKED:
            case TotalCaptureResultProxy::CONTROL_AF_STATE_NOT_FOCUSED_LOCKED:
            case TotalCaptureResultProxy::CONTROL_AF_STATE_PASSIVE_FOCUSED:
            case TotalCaptureResultProxy::CONTROL_AF_STATE_PASSIVE_UNFOCUSED:
                return true;
            default:
                return false;
        }
    }
};

// Dummy implementation of TotalCaptureResultProxy for demonstration purposes
class DummyTotalCaptureResultProxy : public TotalCaptureResultProxy {
public:
    int get(LensState key) const override {
        return LENS_STATE_STATIONARY;
    }

    int get(AEState key) const override {
        return CONTROL_AE_STATE_CONVERGED;
    }

    int get(AFState key) const override {
        return CONTROL_AF_STATE_FOCUSED_LOCKED;
    }
};

int main() {
    auto metadata = std::make_shared<DummyTotalCaptureResultProxy>();
    AcceptableZslImageFilter filter(true, true);
    bool result = filter.apply(metadata);
    if (result) {
        std::cout << "The ZSL image is acceptable." << std::endl;
    } else {
        std::cout << "The ZSL image is not acceptable." << std::endl;
    }

    return 0;
}