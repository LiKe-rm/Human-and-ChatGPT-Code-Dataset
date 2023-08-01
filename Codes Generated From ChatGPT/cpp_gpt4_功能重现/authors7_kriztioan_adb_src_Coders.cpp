#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>
#include <cctype>

class Coders {
public:
    std::string urlDecode(const std::string& input);
    std::string urlEncode(const std::string& input);
    std::string latexDecode(const std::string& input);
    std::string htmlEncode(const std::string& input);
    std::string htmlToXML(const std::string& input);

private:
    char hexToChar(const std::string& hex);
    std::string charToHex(char ch);
};

char Coders::hexToChar(const std::string& hex) {
    int value = 0;
    std::stringstream ss;
    ss << std::hex << hex;
    ss >> value;
    return static_cast<char>(value);
}

std::string Coders::charToHex(char ch) {
    std::stringstream ss;
    ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(static_cast<unsigned char>(ch));
    return ss.str();
}

std::string Coders::urlDecode(const std::string& input) {
    std::string result;
    for (size_t i = 0; i < input.length(); ++i) {
        if (input[i] == '%') {
            if (i + 2 < input.length()) {
                std::string hex = input.substr(i + 1, 2);
                result += hexToChar(hex);
                i += 2;
            }
        } else {
            result += input[i];
        }
    }
    return result;
}

std::string Coders::urlEncode(const std::string& input) {
    std::string result;
    for (const char& ch : input) {
        if (std::isalnum(ch) || ch == '-' || ch == '_' || ch == '.' || ch == '~') {
            result += ch;
        } else {
            result += '%' + charToHex(ch);
        }
    }
    return result;
}

std::string Coders::latexDecode(const std::string& input) {
    std::string result;
    for (size_t i = 0; i < input.length(); ++i) {
        if (input[i] == '\\' && i + 1 < input.length() && input[i + 1] == '\\') {
            result += '\\';
            ++i;
        } else {
            result += input[i];
        }
    }
    return result;
}

std::string Coders::htmlEncode(const std::string& input) {
    std::string result;
    for (const char& ch : input) {
        switch (ch) {
            case '&':
                result += "&amp;";
                break;
            case '<':
                result += "&lt;";
                break;
            case '>':
                result += "&gt;";
                break;
            case ' ':
                result += "&nbsp;";
                break;
            default:
                result += ch;
                break;
        }
    }
    return result;
}

std::string Coders::htmlToXML(const std::string& input) {
    std::string result = htmlEncode(input);
    size_t pos = 0;
    while ((pos = result.find("&nbsp;", pos)) != std::string::npos) {
        result.replace(pos, 6, "&#x20;");
        pos += 6;
    }
    return result;
}

int main() {
    Coders coder;

    std::string url_encoded = "%20Hello%2C%20World%21%3A%29";
    std::string url_decoded = "Hello, World!:)";
    std::string latex_encoded = "Hello\\, \\textbf{World}!";
    std::string html = "<html><head><title>Hello, World!</title></head><body><p>Welcome to the <strong>example</strong> HTML page.</p></body></html>";
    std::cout << "URL Decoded: " << coder.urlDecode(url_encoded) << std::endl;
    std::cout << "URL Encoded: " << coder.urlEncode(url_decoded) << std::endl;
    std::cout << "LaTeX Decoded: " << coder.latexDecode(latex_encoded) << std::endl;
    std::cout << "HTML Encoded: " << coder.htmlEncode(html) << std::endl;
    std::cout << "HTML to XML: " << coder.htmlToXML(html) << std::endl;
    
    return 0;
}