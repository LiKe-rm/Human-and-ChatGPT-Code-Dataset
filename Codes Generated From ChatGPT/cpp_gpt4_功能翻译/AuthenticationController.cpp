#include <crow.h>
#include <bcrypt/BCrypt.hpp>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

// Simulated database
std::unordered_map<std::string, std::string> users;
std::unordered_map<std::string, std::string> hashedPasswords;

class AuthData {
public:
    AuthData(std::string username, std::string password) : username_(std::move(username)), password_(std::move(password)) {}

    const std::string& getUsername() const { return username_; }
    const std::string& getPassword() const { return password_; }

private:
    std::string username_;
    std::string password_;
};

std::string hashPassword(const std::string& password) {
    return BCrypt::generateHash(password);
}

bool authenticate(const std::string& password, const std::string& hashedPassword) {
    return BCrypt::validatePassword(password, hashedPassword);
}

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/register")
    ([] {
        // Render register page
        return crow::response("Register page");
    });

    CROW_ROUTE(app, "/register").methods("POST"_method)
    ([](const crow::request& req) {
        std::string username = req.url_params.get("username");
        std::string password = req.url_params.get("password");

        boost::uuids::uuid id = boost::uuids::random_generator()();
        std::string hashedPassword = hashPassword(password);

        users[username] = boost::uuids::to_string(id);
        hashedPasswords[username] = hashedPassword;

        // Redirect to another page
        return crow::response(303, crow::response::Headers {{"Location", "/scripts"}});
    });

    CROW_ROUTE(app, "/login")
    ([] {
        // Render login page
        return crow::response("Login page");
    });

    CROW_ROUTE(app, "/login").methods("POST"_method)
    ([](const crow::request& req) {
        std::string username = req.url_params.get("username");
        std::string password = req.url_params.get("password");

        auto userIt = users.find(username);
        if (userIt == users.end()) {
            // Render login page with error
            return crow::response("Login page with error");
        } else {
            if (authenticate(password, hashedPasswords[username])) {
                // Redirect to another page
                return crow::response(303, crow::response::Headers {{"Location", "/scripts"}});
            } else {
                // Render login page with error
                return crow::response("Login page with error");
            }
        }
    });

    CROW_ROUTE(app, "/logout").methods("POST"_method)
    ([] {
        // Remove user session and invalidate
        // Redirect to home page
        return crow::response(303, crow::response::Headers {{"Location", "/"}});
    });

    app.port(18080).multithreaded().run();

    return 0;
}
