#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <curl/curl.h>

class Sun {
public:
    Sun(float latitude, float longitude);

    int readSunStore();
    int verifySunStore(float latitude, float longitude);
    int writeSunStore();
    std::string convertUtcToLocal(std::string utc_time);
    std::string https_get(const std::string &url, const std::vector<std::string> &headers, int port = 443, int block_size = 4096);
    std::string rise();
    std::string set();

private:
    float latitude;
    float longitude;
    std::string date;
    std::string sunrise;
    std::string sunset;
    const std::string sun_store_filename = "sun.store";
};

Sun::Sun(float latitude, float longitude) : latitude(latitude), longitude(longitude) {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d");
    date = ss.str();

    std::string api_key = "your_api_key_here";
    std::string url = "https://api.sunrise-sunset.org/json?lat=" + std::to_string(latitude) + "&lng=" + std::to_string(longitude) + "&date=" + date + "&formatted=0";
    std::vector<std::string> headers;
    std::string response = https_get(url, headers);
    size_t sunrise_pos = response.find("\"sunrise\":\"") + 11;
    size_t sunset_pos = response.find("\"sunset\":\"") + 10;
    sunrise = response.substr(sunrise_pos, 19);
    sunset = response.substr(sunset_pos, 19);

    writeSunStore();
}

int Sun::readSunStore() {
    std::ifstream infile(sun_store_filename);
    if (!infile.is_open()) {
        return -1;
    }
    infile >> latitude >> longitude >> date >> sunrise >> sunset;
    infile.close();
    return 0;
}

int Sun::verifySunStore(float latitude, float longitude) {
    if (this->latitude == latitude && this->longitude == longitude) {
        return 0;
    }
    return -1;
}

int Sun::writeSunStore() {
    std::ofstream outfile(sun_store_filename);
    if (!outfile.is_open()) {
        return -1;
    }
    outfile << latitude << " " << longitude << " " << date << " " << sunrise << " " << sunset;
    outfile.close();
    return 0;
}

std::string Sun::convertUtcToLocal(std::string utc_time) {
    std::tm tm_utc = {};
    std::istringstream ss(utc_time);
    ss >> std::get_time(&tm_utc, "%Y-%m-%dT%H:%M:%S");

    std::time_t t_utc = mktime(&tm_utc) - timezone;
    std::tm tm_local = *localtime(&t_utc);
    std::ostringstream os;
    os << std::put_time(&tm_local, "%Y-%m-%d %H:%M:%S");
    return os.str();
}

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp) {
    ((std::string *)userp)->append((char *)buffer, size * nmemb);
    return size * nmemb;
}

std::string Sun::https_get(const std::string &url, const std::vectorstd::string &headers, int port, int block_size) {
    std::string response;
    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_PORT, port);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);

        struct curl_slist *header_list = NULL;
        for (const auto &header : headers) {
            header_list = curl_slist_append(header_list, header.c_str());
        }
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
        if (header_list) {
            curl_slist_free_all(header_list);
        }
    }
    curl_global_cleanup();

    return response;
}

std::string Sun::rise() {
    return convertUtcToLocal(sunrise);
}

std::string Sun::set() {
    return convertUtcToLocal(sunset);
}
