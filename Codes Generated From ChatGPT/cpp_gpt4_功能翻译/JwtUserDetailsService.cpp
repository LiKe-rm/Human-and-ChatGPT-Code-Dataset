#include <string>
#include <vector>
#include <iostream>

class SysUser {
public:
    std::string account;
    std::string password;
    std::string name;

    SysUser(std::string account, std::string password, std::string name)
        : account(account), password(password), name(name) {}
};

class SysUserService {
public:
    SysUser* findOne(std::string account) {
        // This would normally be a database call
        if (account == "test") {
            return new SysUser("test", "password", "Test User");
        }
        return nullptr;
    }
};

class JwtUserDetails {
public:
    std::string account;
    std::string password;
    std::vector<std::string> authorities;
    std::string name;

    JwtUserDetails(std::string account, std::string password, std::vector<std::string> authorities)
        : account(account), password(password), authorities(authorities) {}
    void setName(const std::string& name) {
        this->name = name;
    }

    std::string getName() {
        return this->name;
    }
};

class JwtUserDetailsService {
    SysUserService userService;

public:
    JwtUserDetailsService(SysUserService userService) : userService(userService) {}

    SysUser* getByAccount(const std::string& name) {
        return userService.findOne(name);
    }

    JwtUserDetails* loadUserByUsername(const std::string& account) {
        if(account.empty()) {
            return nullptr;
        }
        SysUser* entity = getByAccount(account);
        if(entity != nullptr) {
            JwtUserDetails* jwtUserDetails = new JwtUserDetails(account, entity->password, {});
            jwtUserDetails->setName(entity->name);
            return jwtUserDetails;
        }else {
            return nullptr;
        }
    }
};

int main() {
    SysUserService sysUserService;
    JwtUserDetailsService jwtUserDetailsService(sysUserService);

    JwtUserDetails* userDetails = jwtUserDetailsService.loadUserByUsername("test");
    if (userDetails != nullptr) {
        std::cout << "User: " << userDetails->getName() << std::endl;
    } else {
        std::cout << "User not found." << std::endl;
    }

    return 0;
}

   
