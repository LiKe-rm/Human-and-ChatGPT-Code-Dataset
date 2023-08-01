#include "crow_all.h"
#include <sstream>
#include <nlohmann/json.hpp>

class QuickException : public std::exception {
    int code;
    std::string message;

public:
    QuickException(int code, const std::string& message)
        : code(code), message(message) {}

    const char* what() const throw() {
        return message.c_str();
    }

    int getCode() const {
        return code;
    }
};

crow::response handleException(const QuickException& ex) {
    std::ostringstream os;
    os << "{ \"code\": " << ex.getCode() << ", \"message\": \"" << ex.what() << "\" }";
    crow::response res{500};
    res.write(os.str());
    return res;
}

crow::response handleException(const std::exception& ex) {
    std::ostringstream os;
    os << "{ \"code\": 500, \"message\": \"" << ex.what() << "\" }";
    crow::response res{500};
    res.write(os.str());
    return res;
}

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
    .methods("GET"_method)
    ([]() {
        throw QuickException(1001, "A quick exception occurred");
        return "";
    });

    app.error_handler = [](int /*ev*/, const crow::request& /*req*/, const crow::response& /*res*/, std::string /*message*/) {
        // Handle all other exceptions
        return handleException(std::runtime_error("Unknown error"));
    };

    try {
        app.run();
    }
    catch (const QuickException& ex) {
        handleException(ex);
    }
    catch (const std::exception& ex) {
        handleException(ex);
    }

    return 0;
}
