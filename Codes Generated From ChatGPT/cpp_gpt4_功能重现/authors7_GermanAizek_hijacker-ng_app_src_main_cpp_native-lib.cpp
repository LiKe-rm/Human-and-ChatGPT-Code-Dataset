#include <jni.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>

extern "C" {
    JNIEXPORT jint JNICALL Java_com_example_androidapp_JniInterface_processData(JNIEnv* env, jobject obj, jstring jstr);
}

// 函数原型
void addST(const std::string& mac, const std::string& bssid, int pwr, int lost, int frames, const std::vector<std::string>& probes);
void addAP(const std::string& bssid, int pwr, int beacons, int data, int ivs, int ch, const std::string& enc, const std::string& cipher, const std::string& auth, const std::string& essid);

JNIEXPORT jint JNICALL Java_com_example_androidapp_JniInterface_processData(JNIEnv* env, jobject obj, jstring jstr) {
    const char* str = env->GetStringUTFChars(jstr, 0);
    std::string input_str(str);
    env->ReleaseStringUTFChars(jstr, str);

    // 去掉换行符和空格字符
    input_str.erase(std::remove_if(input_str.begin(), input_str.end(), ::isspace), input_str.end());

    std::istringstream iss(input_str);
    std::string prefix;
    iss >> prefix;

    if (prefix == "STA") {
        std::string mac, bssid;
        int pwr, lost, frames;
        std::vector<std::string> probes;

        iss >> mac >> bssid >> pwr >> lost >> frames;

        std::string probe;
        while (iss >> probe) {
            probes.push_back(probe);
        }

        addST(mac, bssid, pwr, lost, frames, probes);
    } else if (prefix == "AP") {
        std::string bssid, enc, cipher, auth, essid;
        int pwr, beacons, data, ivs, ch;

        iss >> bssid >> pwr >> beacons >> data >> ivs >> ch >> enc >> cipher >> auth >> essid;

        addAP(bssid, pwr, beacons, data, ivs, ch, enc, cipher, auth, essid);
    }

    return 0;
}

void addST(const std::string& mac, const std::string& bssid, int pwr, int lost, int frames, const std::vector<std::string>& probes) {
    // 在此实现将STA添加到应用程序的逻辑
}

void addAP(const std::string& bssid, int pwr, int beacons, int data, int ivs, int ch, const std::string& enc, const std::string& cipher, const std::string& auth, const std::string& essid) {
    // 在此实现将AP添加到应用程序的逻辑
}
