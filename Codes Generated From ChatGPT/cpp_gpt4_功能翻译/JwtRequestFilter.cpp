#include <jwt-cpp/jwt.h>
#include <string>
#include <iostream>
#include <map>

class JwtTokenProvider {
    std::string secret;

public:
    JwtTokenProvider(const std::string& secret) : secret(secret) {}

    bool validate(const std::string& token) {
        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{secret})
            .with_issuer("auth0");
        try {
            verifier.verify(jwt::decode(token));
            return true;
        } catch (std::exception& e) {
            std::cerr << "Token validation failed: " << e.what() << std::endl;
            return false;
        }
    }

    std::string getUserFromToken(const std::string& token) {
        auto decoded_token = jwt::decode(token);
        return decoded_token.get_payload_claim("sub").as_string();
    }
};

class JwtRequestFilter {
    JwtTokenProvider jwtTokenProvider;
    
public:
    JwtRequestFilter(const std::string& secret) : jwtTokenProvider(secret) {}

    void doFilter(const std::map<std::string, std::string>& headers) {
        auto it = headers.find("Authorization");
        if(it == headers.end() || it->second.substr(0, 7) != "Bearer ") {
            return;
        }

        std::string token = it->second.substr(7);
        if(!jwtTokenProvider.validate(token)) {
            return;
        }

        std::string userDetails = jwtTokenProvider.getUserFromToken(token);
        // perform some action with the user details
    }
};

int main() {
    std::string secret = "your_secret_key";
    JwtRequestFilter jwtRequestFilter(secret);

    std::map<std::string, std::string> headers = {
        {"Authorization", "Bearer your_jwt_token"}
    };

    jwtRequestFilter.doFilter(headers);

    return 0;
}
