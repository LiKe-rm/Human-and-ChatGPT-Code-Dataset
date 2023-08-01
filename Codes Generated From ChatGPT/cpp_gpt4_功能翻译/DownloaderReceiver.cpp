#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <curl/curl.h>

class DownloadManager {
public:
    typedef std::function<void(const std::string&)> DownloadCompleteCallback;

private:
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
        size_t totalSize = size * nmemb;
        userp->append((char*)contents, totalSize);
        return totalSize;
    }

    std::map<long, DownloadCompleteCallback> downloadCallbacks;
    long downloadIdCounter = 0;

public:
    long downloadFile(const std::string& url, DownloadCompleteCallback callback) {
        long downloadId = downloadIdCounter++;
        downloadCallbacks[downloadId] = callback;

        CURL* curl;
        CURLcode res;
        std::string readBuffer;

        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();

        if(curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            if(res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            } else {
                downloadComplete(downloadId, readBuffer);
            }
            curl_easy_cleanup(curl);
        }

        curl_global_cleanup();

        return downloadId;
    }

    void downloadComplete(long downloadId, const std::string& downloadedData) {
        if (downloadCallbacks.count(downloadId) > 0) {
            downloadCallbacks[downloadId](downloadedData);
            downloadCallbacks.erase(downloadId);
        }
    }
};

int main() {
    DownloadManager manager;
    manager.downloadFile("http://example.com", [](const std::string& data) {
        std::cout << "Download complete. Data: " << data << std::endl;
    });

    // Do other stuff...

    return 0;
}
