#include <iostream>
#include <string>
#include <regex>
#include <unordered_map>
#include <random>
#include <ctime>
#include <httplib.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::unordered_map<std::string, std::string> samples = {
    {"sample1", "Sample source code 1"},
    {"sample2", "Sample source code 2"},
    // Add more sample source codes here
};

std::string compile_source(const std::string &source, bool enable_optimization) {
    // Implement the source code compilation logic here
    return "Compiled source code";
}

int main() {
    httplib::Server svr;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, samples.size() - 1);

    svr.Get("/", [&](const httplib::Request &req, httplib::Response &res) {
        std::string id = req.get_param_value("s");
        bool enable_optimization = req.get_param_value("optimization") == "true";

        std::string sample_name;
        std::string source_code;
        if (samples.find(id) != samples.end()) {
            sample_name = id;
            source_code = samples[id];
        } else if (id == "clean") {
            sample_name = "";
            source_code = "";
        } else if (std::regex_match(id, std::regex("[a-f0-9]{8}(?:-[a-f0-9]{4}){3}-[a-f0-9]{12}"))) {
            // Add code to fetch the source code from the repository
        } else {
            int index = dist(gen);
            auto it = samples.begin();
            std::advance(it, index);
            sample_name = it->first;
            source_code = it->second;
        }

        std::string compiled_code = compile_source(source_code, enable_optimization);

        json response;
        response["sample_name"] = sample_name;
        response["source_code"] = source_code;
        response["compiled_code"] = compiled_code;
        res.set_content(response.dump(), "application/json");
    });

    svr.listen("localhost", 8080);
}
