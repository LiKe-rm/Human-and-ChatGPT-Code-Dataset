#include <string>
#include <vector>
#include <iostream>

class HomePageData {
public:
    HomePageData(
        const std::string &id,
        const std::string &sample,
        const std::string &source,
        int source_loc,
        const std::string &compiled,
        int compiled_loc,
        const std::vector<std::string> &syntax_errors,
        bool enable_optimization
    ) :
        id_(id),
        sample_(sample),
        source_(source),
        source_loc_(source_loc),
        compiled_(compiled),
        compiled_loc_(compiled_loc),
        syntax_errors_(syntax_errors),
        enable_optimization_(enable_optimization) {}

    std::string getId() const {
        return id_;
    }

    std::string getSample() const {
        return sample_;
    }

    std::string getSource() const {
        return source_;
    }

    int getSourceLoc() const {
        return source_loc_;
    }

    std::string getCompiled() const {
        return compiled_;
    }

    int getCompiledLoc() const {
        return compiled_loc_;
    }

    std::vector<std::string> getSyntaxErrors() const {
        return syntax_errors_;
    }

    bool getEnableOptimization() const {
        return enable_optimization_;
    }

    bool isLoggedIn() const {
        return false;
    }

private:
    std::string id_;
    std::string sample_;
    std::string source_;
    int source_loc_;
    std::string compiled_;
    int compiled_loc_;
    std::vector<std::string> syntax_errors_;
    bool enable_optimization_;
};

int main() {
    std::vector<std::string> errors = {"Syntax error 1", "Syntax error 2"};

    HomePageData home_page_data(
        "123",
        "sample",
        "source code",
        10,
        "compiled code",
        20,
        errors,
        true
    );

    std::cout << "ID: " << home_page_data.getId() << std::endl;
    std::cout << "Sample: " << home_page_data.getSample() << std::endl;
    std::cout << "Source: " << home_page_data.getSource() << std::endl;
    std::cout << "Source LOC: " << home_page_data.getSourceLoc() << std::endl;
    std::cout << "Compiled: " << home_page_data.getCompiled() << std::endl;
    std::cout << "Compiled LOC: " << home_page_data.getCompiledLoc() << std::endl;
    std::cout << "Enable optimization: " << home_page_data.getEnableOptimization() << std::endl;

    auto syntax_errors = home_page_data.getSyntaxErrors();
    std::cout << "Syntax errors: " << std::endl;
    for (const auto &error : syntax_errors) {
        std::cout << "  - " << error << std::endl;
    }

    return 0;
}
