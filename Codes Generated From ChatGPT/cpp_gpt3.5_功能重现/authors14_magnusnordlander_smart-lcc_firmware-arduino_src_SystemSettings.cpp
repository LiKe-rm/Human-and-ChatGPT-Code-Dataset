#include <iostream>
#include <fstream>
#include <string>
#include "PicoQueue.h"
#include "FileIO.h"

#define SETTING_FILENAME "settings.txt"
#define SETTING_VERSION 1

struct SettingStruct {
    bool sleep_mode;
    bool energy_saving_mode;
    int target_brewing_temperature;
    int target_service_temperature;
};

class SystemSettings {
public:
    SystemSettings() : queue(100), file_io(SETTING_FILENAME) {
        load_settings();
    }
    ~SystemSettings() {
        save_settings();
    }
    void set_sleep_mode(bool value) {
        settings.sleep_mode = value;
        send_command("set_sleep_mode", value);
    }
    void set_energy_saving_mode(bool value) {
        settings.energy_saving_mode = value;
        send_command("set_energy_saving_mode", value);
    }
    void set_target_brewing_temperature(int value) {
        settings.target_brewing_temperature = value;
        send_command("set_target_brewing_temperature", value);
    }
    void set_target_service_temperature(int value) {
        settings.target_service_temperature = value;
        send_command("set_target_service_temperature", value);
    }
private:
    SettingStruct settings;
    PicoQueue<std::pair<std::string, int>> queue;
    FileIO file_io;

    void load_settings() {
        int version;
        std::ifstream infile(SETTING_FILENAME);
        if (infile.is_open()) {
            infile >> version;
            if (version == SETTING_VERSION) {
                infile >> settings.sleep_mode >> settings.energy_saving_mode 
                    >> settings.target_brewing_temperature >> settings.target_service_temperature;
            }
            infile.close();
        }
    }
    void save_settings() {
        std::ofstream outfile(SETTING_FILENAME);
        if (outfile.is_open()) {
            outfile << SETTING_VERSION << "\n";
            outfile << settings.sleep_mode << " " << settings.energy_saving_mode << " "
                << settings.target_brewing_temperature << " " << settings.target_service_temperature << "\n";
            outfile.close();
        }
    }
    void send_command(const std::string& command, int value) {
        std::pair<std::string, int> cmd(command, value);
        queue.push(cmd);
        // send cmd asynchronously to SystemController
    }
    void send_command(const std::string& command, bool value) {
        std::pair<std::string, int> cmd(command, value ? 1 : 0);
        queue.push(cmd);
        // send cmd asynchronously to SystemController
    }
};
