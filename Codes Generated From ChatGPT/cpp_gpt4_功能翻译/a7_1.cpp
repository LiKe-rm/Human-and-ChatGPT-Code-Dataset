#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <mutex>

class Fragment {
public:
    int A05 = 0;
    int A01 = 0;
};

class AnonymousClass5d {
public:
    bool A00 = false;
};

class AbstractC00409v {
public:
    virtual void A3e(std::shared_ptr<Fragment> fragment, std::shared_ptr<AnonymousClass5d> r5) = 0;
    virtual void A41(std::shared_ptr<Fragment> fragment, std::shared_ptr<AnonymousClass5d> r5) = 0;
    virtual ~AbstractC00409v() = default;
};

class AbstractC00279a {
public:
    void A06(std::shared_ptr<Fragment> fragment) {
        std::cout << "Called AbstractC00279a::A06 with fragment A05 = " << fragment->A05 << std::endl;
    }

    void A0X(std::shared_ptr<Fragment> fragment, int i) {
        std::cout << "Called AbstractC00279a::A0X with fragment A05 = " << fragment->A05 << " and i = " << i << std::endl;
    }

    std::unordered_map<std::shared_ptr<Fragment>, std::unordered_set<std::shared_ptr<AnonymousClass5d>>> A0B;
};

class a7 : public AbstractC00409v {
public:
    a7(std::shared_ptr<AbstractC00279a> r1) : A00(r1) {}

    void A3e(std::shared_ptr<Fragment> fragment, std::shared_ptr<AnonymousClass5d> r5) override {
        bool z;
        std::unique_lock<std::mutex> lock(mutex_);
        z = r5->A00;
        lock.unlock();

        if (!z) {
            auto& r2 = A00;
            auto it = r2->A0B.find(fragment);
            if (it != r2->A0B.end() && it->second.erase(r5) && it->second.empty()) {
                r2->A0B.erase(it);
                if (fragment->A05 < 3) {
                    r2->A06(fragment);
                    int i = fragment->A01;
                    r2->A0X(fragment, i);
                }
            }
        }
    }

    void A41(std::shared_ptr<Fragment> fragment, std::shared_ptr<AnonymousClass5d> r5) override {
        auto& r2 = A00;
        if (r2->A0B.find(fragment) == r2->A0B.end()) {
            r2->A0B[fragment] = std::unordered_set<std::shared_ptr<AnonymousClass5d>>();
        }
        r2->A0B[fragment].insert(r5);
    }

private:
    std::shared_ptr<AbstractC00279a> A00;
    std::mutex mutex_;
};

int main() {
    auto r1 = std::make_shared<AbstractC00279a>();
    a7 a7_instance(r1);

    auto fragment = std::make_shared<Fragment>();
    fragment->A05 = 2;

    auto r5 = std::make_shared<AnonymousClass5d>();

    a7_instance.A41(fragment, r5);
    a7_instance.A3e(fragment, r5);

    return 0;
}
