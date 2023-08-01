#include <iostream>
#include <map>
#include <string>

namespace turtle {
    // 枚举类型，表示词法单元的类型
    enum TokenType {
        TOK_PLUS,
        TOK_MINUS,
        TOK_STAR,
        TOK_SLASH,
        TOK_INTEGER,
        TOK_FLOAT,
        TOK_EOF
    };

    // 结构体，用于识别不同类型的字符
    struct CharType {
        bool is_digit;
        bool is_dot;
        bool is_plus;
        bool is_minus;
        bool is_star;
        bool is_slash;
    };

    // 常量，用于表示在处理字符串时需要采取的操作
    const CharType CHARTYPE_TABLE[] = {
        /* 0 */ { false, false, false, false, false, false }, // nul
        /* 1 */ { false, false, false, false, false, false }, // soh
        /* 2 */ { false, false, false, false, false, false }, // stx
        /* 3 */ { false, false, false, false, false, false }, // etx
        /* 4 */ { false, false, false, false, false, false }, // eot
        /* 5 */ { false, false, false, false, false, false }, // enq
        /* 6 */ { false, false, false, false, false, false }, // ack
        /* 7 */ { false, false, false, false, false, false }, // bel
        /* 8 */ { false, false, false, false, false, false }, // bs
        /* 9 */ { false, false, false, false, false, false }, // ht
        /* 10 */{ false, false, false, false, false, false }, // nl
        /* 11 */{ false, false, false, false, false, false }, // vt
        /* 12 */{ false, false, false, false, false, false }, // np
        /* 13 */{ false, false, false, false, false, false }, // cr
        /* 14 */{ false, false, false, false, false, false }, // so
        /* 15 */{ false, false, false, false, false, false }, // si
        /* 16 */{ false, false, false, false, false, false }, // dle
        /* 17 */{ false, false, false, false, false, false }, // dc1
        /* 18 */{ false, false, false, false, false, false }, // dc2
        /* 19 */{ false, false, false, false, false, false }, // dc3
        /* 20 */{ false, false, false, false, false, false }, // dc4
        /* 21 */{ false, false, false, false, false, false }, // nak
        /* 22 */{ false, false, false, false, false, false }, // syn
        /* 23 */{ false, false, false, false, false, false }, // etb
        /* 24 */{ false, false, false, false, false, false }, // can
        /* 25 */{ false, false, false, false, false, false }, // em
        /* 26 */{ false, false, false, false, false, false }, // sub
        //.......
        };

    // 类，描述了如何识别一个特定类型的词法单元，以及如何将其解析成一个标记
    class Token {
    public:
        Token(TokenType type, const std::string& lexeme, double value)
            : type_(type), lexeme_(lexeme), value_(value) {}

        TokenType type() const { return type_; }
        const std::string& lexeme() const { return lexeme_; }
        double value() const { return value_; }

    private:
        TokenType type_;
        std::string lexeme_;
        double value_;
    };

    // 数组，存储不同类型的词法单元的对象
    Token TOKEN_TABLE[] = {
        Token(TOK_PLUS, "+", 0),
        Token(TOK_MINUS, "-", 0),
        Token(TOK_STAR, "*", 0),
        Token(TOK_SLASH, "/", 0),
        Token(TOK_INTEGER, "", 0),
        Token(TOK_FLOAT, "", 0),
        Token(TOK_EOF, "", 0)
    };

    // 数组，将不同类型的字符映射到结构体值
    const int MAX_CHAR = 127;
    CharType CHAR_TABLE[MAX_CHAR + 1];
    void init_char_table() {
        for (int i = 0; i <= MAX_CHAR; i++) {
            if (i >= '0' && i <= '9') {
                CHAR_TABLE[i] = CHARTYPE_TABLE['0'];
            } else if (i == '+') {
                CHAR_TABLE[i] = CHARTYPE_TABLE['+'];
            } else if (i == '-') {
                CHAR_TABLE[i] = CHARTYPE_TABLE['-'];
            } else if (i == '*') {
                CHAR_TABLE[i] = CHARTYPE_TABLE['*'];
            } else if (i == '/') {
                CHAR_TABLE[i] = CHARTYPE_TABLE['/'];
            } else if (i == '.') {
                CHAR_TABLE[i] = CHARTYPE_TABLE['.'];
            } else {
                CHAR_TABLE[i] = CHARTYPE_TABLE[0];
            }
        }
    }

    // map，将不同类型的结构体值映射到枚举值
    std::map<CharType, TokenType> CHAR_TYPE_MAP;
    void init_char_type_map() {
        CHAR_TYPE_MAP[CHARTYPE_TABLE['+']] = TOK_PLUS;
        CHAR_TYPE_MAP[CHARTYPE_TABLE['-']] = TOK_MINUS;
        CHAR_TYPE_MAP[CHARTYPE_TABLE['*']] = TOK_STAR;
        CHAR_TYPE_MAP[CHARTYPE_TABLE['/']] = TOK_SLASH;
        CHAR_TYPE_MAP[CHARTYPE_TABLE['.']] = TOK_FLOAT;
        for (int i = '0'; i <= '9'; i++) {
            CHAR_TYPE_MAP[CHARTYPE_TABLE[i]] = TOK_INTEGER;
        }
    }

    // 函数，用于从枚举获取对象
    Token get_token(TokenType type) {
        return TOKEN_TABLE[type];
    }

    // 函数，用于从结构体值获取对象
    Token get_token(const CharType& chartype) {
        TokenType type = CHAR_TYPE_MAP[chartype];
        return TOKEN_TABLE[type];
    }

    // 初始化函数，初始化 CHAR_TABLE 和 CHAR_TYPE_MAP
    void init() {
        init_char_table();
        init_char_type_map();
    }
}



