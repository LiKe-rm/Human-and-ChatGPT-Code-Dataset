#include <iostream>
#include <fstream>

class Settings {
public:
    Settings() {
        // Try to read from flash memory
        std::ifstream ifs("settings.txt");
        if (ifs.is_open()) {
            ifs >> productivity >> clean_target_time >> grind_target_time >> grind_target_weight >> scale_calibration >> reaction_time;
            ifs.close();
        } else {
            // Use default values if read fails
            productivity = 10;
            clean_target_time = 300;
            grind_target_time = 45;
            grind_target_weight = 20;
            scale_calibration = 1.0;
            reaction_time = 10;
        }
    }

    int get_productivity() const {
        return productivity;
    }

    void set_productivity(int value) {
        if (value != productivity) {
            productivity = value;
            write_to_flash();
        }
    }

    int get_clean_target_time() const {
        return clean_target_time;
    }

    void set_clean_target_time(int value) {
        if (value != clean_target_time) {
            clean_target_time = value;
            write_to_flash();
        }
    }

    int get_grind_target_time() const {
        return grind_target_time;
    }

    void set_grind_target_time(int value) {
        if (value != grind_target_time) {
            grind_target_time = value;
            write_to_flash();
        }
    }

    int get_grind_target_weight() const {
        return grind_target_weight;
    }

    void set_grind_target_weight(int value) {
        if (value != grind_target_weight) {
            grind_target_weight = value;
            write_to_flash();
        }
    }

    double get_scale_calibration() const {
        return scale_calibration;
    }

    void set_scale_calibration(double value) {
        if (value != scale_calibration) {
            scale_calibration = value;
            write_to_flash();
        }
    }

    int get_reaction_time() const {
        return reaction_time;
    }

    void set_reaction_time(int value) {
        if (value != reaction_time) {
            reaction_time = value;
            write_to_flash();
        }
    }

private:
    int productivity;
    int clean_target_time;
    int grind_target_time;
    int grind_target_weight;
    double scale_calibration;
    int reaction_time;

    void write_to_flash() {
        std::ofstream ofs("settings.txt");
        ofs << productivity << " " << clean_target_time << " " << grind_target_time << " " << grind_target_weight << " " << scale_calibration << " " << reaction_time;
        ofs.close();
    }
};

int main() {
    Settings s;
    std::cout << "Productivity: " << s.get_productivity() << std::endl;
    std::cout << "Clean target time: " << s.get_clean_target_time() << std::endl;
    std::cout << "Grind target time: " << s.get_grind_target_time() << std::endl;
    std::cout << "Grind target weight: " << s.get_grind_target_weight() << std::endl;
    std::cout << "Scale calibration: " << s.get_scale_calibration() << std::endl;
    std::cout << "Reaction time: " << s.get_reaction_time() << std::endl;

    s.set_productivity(20);
    s.set_scale_calibration(0.95);

    std::cout << "Productivity: " << s.get_productivity() << std::endl;
    std::cout << "Scale calibration: " << s.get_scale_calibration() << std::endl;

    return 0;
}
