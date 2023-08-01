#include <iostream>
#include <string>
#include <set>
#include <unordered_set>
#include <iterator>
#include <functional>

class UH0 {};

class AbstractC3087il0 {
public:
    virtual void d(UH0 uh0, int i) = 0;
    virtual void f(UH0 uh0, int i) = 0;
    virtual ~AbstractC3087il0() = default;
};

class C2746gl0 {
public:
    void b(UH0 uh0, int i) {
        std::cout << "Called C2746gl0::b with i = " << i << std::endl;
    }
};

class N {
public:
    static void Me60Lv4_(const std::string& str, bool value) {
        std::cout << "Called N::Me60Lv4_ with str = " << str << " and value = " << value << std::endl;
    }

    static void MC39_Sil(const std::string& str, bool value) {
        std::cout << "Called N::MC39_Sil with str = " << str << " and value = " << value << std::endl;
    }
};

class A60 : public AbstractC3087il0 {
public:
    void a(int i) {
        std::cout << "Called A60::a with i = " << i << std::endl;
    }

    void d(UH0 uh0, int i) override {
        if (i == 1) {
            F.b(uh0, 2);
            return;
        }

        std::set<std::string> treeSet(G.begin(), G.end());
        for (const std::string& str : H) {
            treeSet.erase(str);
        }

        for (const std::string& str : treeSet) {
            N::Me60Lv4_(str, true);
            N::MC39_Sil(str, true);
        }

        std::unordered_set<std::string> hashSet(H.begin(), H.end());
        for (const std::string& str : G) {
            hashSet.erase(str);
        }

        for (const std::string& str : hashSet) {
            N::Me60Lv4_(str, false);
            N::MC39_Sil(str, false);
        }

        F.b(uh0, 1);
    }

    void f(UH0 uh0, int i) override {
        if (i == 1) {
            a(1);
        } else {
            a(2);
        }
    }

    C2746gl0 F;
    std::unordered_set<std::string> G;
    std::unordered_set<std::string> H;
};

int main() {
    A60 a60;
    a60.G.insert({"apple", "banana", "cherry"});
    a60.H.insert({"banana", "pear", "grape"});

    UH0 uh0;
    a60.d(uh0, 1);
    a60.d(uh0, 2);
    a60.f(uh0, 1);
    a60.f(uh0, 2);

    return 0;
}
