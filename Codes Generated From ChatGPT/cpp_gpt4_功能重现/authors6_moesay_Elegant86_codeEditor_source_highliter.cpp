#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QTextDocument>

class AsmHighlighter : public QSyntaxHighlighter {
public:
    AsmHighlighter(QTextDocument *parent = nullptr) : QSyntaxHighlighter(parent) {
        // 保留字
        QTextCharFormat keywordFormat;
        keywordFormat.setForeground(Qt::blue);
        QStringList keywordPatterns = {
            "\\bmov\\b", "\\badd\\b", "\\bsub\\b", "\\bmul\\b", "\\bdiv\\b", "\\bpush\\b", "\\bpop\\b", "\\bcall\\b", "\\bret\\b", "\\bjmp\\b"
        };
        for (const QString &pattern : keywordPatterns) {
            hRulesVec.push_back({QRegularExpression(pattern), keywordFormat});
        }

        // 寄存器
        QTextCharFormat registerFormat;
        registerFormat.setForeground(Qt::magenta);
        QStringList registerPatterns = {
            "\\b(?:eax|ebx|ecx|edx|esi|edi|esp|ebp|r8|r9|r10|r11|r12|r13|r14|r15)\\b"
        };
        for (const QString &pattern : registerPatterns) {
            hRulesVec.push_back({QRegularExpression(pattern), registerFormat});
        }

        // 指令
        QTextCharFormat instructionFormat;
        instructionFormat.setForeground(Qt::blue);
        instructionFormat.setFontItalic(true);
        instructionFormat.setFontWeight(QFont::Bold);
        QStringList instructionPatterns = {
            "\\b(?:int|nop)\\b"
        };
        for (const QString &pattern : instructionPatterns) {
            hRulesVec.push_back({QRegularExpression(pattern), instructionFormat});
        }

        // 数字
        QTextCharFormat numberFormat;
        numberFormat.setForeground(Qt::cyan);
        QStringList numberPatterns = {
            "\\b\\d+\\b"
        };
        for (const QString &pattern : numberPatterns) {
            hRulesVec.push_back({QRegularExpression(pattern), numberFormat});
        }

        // 注释
        QTextCharFormat commentFormat;
        commentFormat.setForeground(Qt::green);
        QStringList commentPatterns = {
            ";[^\n]*"
        };
        for (const QString &pattern : commentPatterns) {
            hRulesVec.push_back({QRegularExpression(pattern), commentFormat});
        }
    }

protected:
    void highlightBlock(const QString &text) override {
        for (const auto &rule : hRulesVec) {
            QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
            while (matchIterator.hasNext()) {
                QRegularExpressionMatch match = matchIterator.next();
                setFormat(match.capturedStart(), match.capturedLength(), rule.format);
            }
        }
    }

private:
    struct st_HighlightRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };

    std::vector<st_HighlightRule> hRulesVec;
};
