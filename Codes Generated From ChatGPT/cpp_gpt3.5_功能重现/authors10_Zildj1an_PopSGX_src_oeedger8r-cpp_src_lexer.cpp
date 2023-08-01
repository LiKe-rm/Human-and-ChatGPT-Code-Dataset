#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>

enum class TokenType {
    EndOfFile,
    Identifier,
    Number,
    LeftParenthesis,
    RightParenthesis,
    LeftBrace,
    RightBrace,
    LeftBracket,
    RightBracket,
    Semicolon,
    Colon,
    Comma,
    Operator,
    Keyword
};

struct Token {
    TokenType type;
    std::string value;
    int line;
    int column;
};

class Lexer {
public:
    Lexer(const std::string& file) {
        std::ifstream source_file(file);
        if (!source_file.is_open()) {
            throw std::runtime_error("Unable to open source file: " + file);
        }
        source_code = std::string(std::istreambuf_iterator<char>(source_file), std::istreambuf_iterator<char>());
        current_position = 0;
        current_line = 1;
        current_column = 1;
    }

    std::vector<Token> tokenize() {
        std::vector<Token> tokens;
        Token token;
        do {
            token = getNextToken();
            tokens.push_back(token);
        } while (token.type != TokenType::EndOfFile);

        return tokens;
    }

private:
    std::string source_code;
    size_t current_position;
    int current_line;
    int current_column;

    Token getNextToken() {
        skipWhitespace();
        if (current_position >= source_code.length()) {
            return makeToken(TokenType::EndOfFile);
        }
        char current_char = source_code[current_position];
        if (isalpha(current_char) || current_char == '_') {
            return parseIdentifierOrKeyword();
        }
        if (isdigit(current_char)) {
            return parseNumber();
        }
        if (ispunct(current_char)) {
            return parsePunctuationOrOperator();
        }
        return makeToken(TokenType::EndOfFile);
    }

    void skipWhitespace() {
        while (current_position < source_code.length()) {
            char current_char = source_code[current_position];
            if (isspace(current_char)) {
                if (current_char == '\n') {
                    current_line++;
                    current_column = 1;
                } else {
                    current_column++;
                }
                current_position++;
            } else {
                break;
            }
        }
    }

    Token parseIdentifierOrKeyword() {
        std::string identifier;
        while (current_position < source_code.length()) {
            char current_char = source_code[current_position];
            if (isalnum(current_char) || current_char == '_') {
                identifier += current_char;
                current_position++;
                current_column++;
            } else {
                break;
            }
        }

        if (isKeyword(identifier)) {
            return makeToken(TokenType::Keyword, identifier);
        }
        return makeToken(TokenType::Identifier, identifier);
    }

    Token parseNumber() {
        std::string number;
        while (current_position < source_code.length()) {
            char current_char = source_code[current_position];
            if (isdigit(current_char)) {
                number += current_char;
                current_position++;
                current_column++;
            } else {
                break;
            }
        }
        return makeToken(TokenType::Number, number);
    }

    Token parsePunctuationOrOperator() {
        char current_char = source_code[current_position];
        current_position++;
        current_column++;

        switch (current_char) {
            case '(':
                return makeToken(TokenType::LeftParenthesis, "(");
            case ')':
                return makeToken(TokenType::RightParenthesis, ")");
            case '{':
                return makeToken(TokenType::LeftBrace, "{");
            case '}':
                return makeToken(TokenType::RightBrace, "}");
            case '[':
                return makeToken(TokenType::LeftBracket, "[");
            case ']':
                return makeToken(TokenType::RightBracket, "]");
            case ';':
                return makeToken(TokenType::Semicolon, ";");
            case ':':
                return makeToken(TokenType::Colon, ":");
            case ',':
                return makeToken(TokenType::Comma, ",");
            default:
                if (ispunct(current_char)) {
                    return makeToken(TokenType::Operator, std::string(1, current_char));
                } else {
                    std::cerr << "Syntax error at line " << current_line << ", column " << current_column << ": Invalid character " << current_char << std::endl;
                    exit(EXIT_FAILURE);
                }
        }
    }

    Token makeToken(TokenType type, const std::string& value = "") {
        return Token{type, value, current_line, current_column};
    }

    bool isKeyword(const std::string& identifier) {
        static const std::vector<std::string> keywords = {
            "auto", "break", "case", "char", "const", "continue", "default", "do",
            "double", "else", "enum", "extern", "float", "for", "goto", "if",
            "int", "long", "register", "return", "short", "signed", "sizeof", "static",
            "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
        };

        return std::find(keywords.begin(), keywords.end(), identifier) != keywords.end();
    }
};
