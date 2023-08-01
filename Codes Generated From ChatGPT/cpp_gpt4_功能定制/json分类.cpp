#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <filesystem>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;
namespace fs = std::filesystem;

int main() {
    string folder_path = "path/to/folder";
    map<string, vector<json>> json_map;

    for (auto& file : fs::directory_iterator(folder_path)) {
        if (file.path().extension() != ".json") continue;
        ifstream ifs(file.path());
        json j;
        ifs >> j;
        string name = j["name"];
        json_map[name].push_back(j);
    }

    for (auto& [name, jsons] : json_map) {
        cout << name << ":" << endl;
        for (auto& j : jsons) {
            cout << j.dump(4) << endl;
        }
        cout << endl;
    }

    return 0;
}