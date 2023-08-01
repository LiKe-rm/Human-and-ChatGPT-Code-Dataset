#include <cpprest/http_listener.h>
#include <cpprest/json.h>

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

class SysMenuController {
private:
    http_listener listener;

public:
    SysMenuController() : listener(uri("http://localhost:8080/v1/system/sysMenu")) {
        listener.support(methods::POST, std::bind(&SysMenuController::handle_post, this, std::placeholders::_1));
        listener.support(methods::PUT, std::bind(&SysMenuController::handle_put, this, std::placeholders::_1));
        // You may add support for other HTTP methods (GET, DELETE) here.
    }

    void handle_post(http_request message) {
        auto paths = uri::split_path(uri::decode(message.relative_uri().path()));

        if (paths.empty()) {
            message.reply(status_codes::BadRequest, U("Invalid URI."));
            return;
        }

        if (paths[0] == "query") {
            // Handle the "query" operation.
        } else if (paths[0] == "get") {
            // Handle the "get" operation.
        } else if (paths[0] == "create") {
            // Handle the "create" operation.
        } else if (paths[0] == "save") {
            // Handle the "save" operation.
        } else if (paths[0] == "delete") {
            // Handle the "delete" operation.
        } else {
            message.reply(status_codes::BadRequest, U("Unknown operation."));
        }
    }

    void handle_put(http_request message) {
        auto paths = uri::split_path(uri::decode(message.relative_uri().path()));

        if (paths.empty()) {
            message.reply(status_codes::BadRequest, U("Invalid URI."));
            return;
        }

        if (paths[0] == "update") {
            // Handle the "update" operation.
        } else {
            message.reply(status_codes::BadRequest, U("Unknown operation."));
        }
    }

    // TODO: Implement handlers for each operation.

    void run() {
        listener
            .open()
            .then([&]() { std::cout << "Starting to listen for HTTP requests." << std::endl; })
            .wait();

        while (true);
    }
};

int main() {
    SysMenuController sysMenuController;
    sysMenuController.run();
    return 0;
}
