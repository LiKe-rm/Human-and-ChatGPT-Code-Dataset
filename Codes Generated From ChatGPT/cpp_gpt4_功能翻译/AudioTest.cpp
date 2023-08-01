#include <iostream>
#include <stdexcept>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, m, h, etc.
using std::chrono::system_clock;

class Test {
public:
    Test(int id, string name): id(id), name(name) {}
    virtual void setUp() = 0;
    virtual void destroy() = 0;
    virtual void onFinish() = 0;
    virtual void onTick() = 0;

protected:
    int id;
    string name;
};

class AudioTest: public Test {
public:
    AudioTest(int id, string name): Test(id, name) {
        loop = 0;
        END = 3;
        text = "";
        tag = "AudioTest";
        audio_flag = true;
        isEnd = false;
    }

    void setUp() override {
        cout << tag + "_start_test\n";
        try {
            startMelody();
        } catch (const exception& e) {
            cerr << e.what() << '\n';
        }
        text = "Speaker test";
    }

    void startMelody() {
        cout << tag + " startMelody\n";
        sleep_for(5s);
        cout << tag + " startMelody end\n";
    }

    void destroy() override {
        loop = 0;
        cout << tag + " finish\n";
        isEnd = false;
    }

    void pass1() {
        cout << tag + " pass " + "loop " + to_string(loop) << "\n";
        switch (loop) {
            case 0:
                text = "Speaker Melody test";
                loop++;
                break;
            case 1:
                text = "loop from MIC test";
                loop++;
                pass1();
                break;
            case 2:
                text = "loop from Sub-MIC test";
                loop++;
                pass1();
                break;
            case END:
                loop++;
                break;
        }
    }

    void onFinish() override {
        cout << tag + " onFinish\n";
        audio_flag = false;
    }

    void onTick() override {}

private:
    int loop;
    int END;
    string text;
    string tag;
    bool isEnd;
    bool audio_flag;
};

int main() {
    AudioTest audioTest(1, "Audio Test");
    audioTest.setUp();
    audioTest.pass1();
    audioTest.destroy();

    return 0;
}
