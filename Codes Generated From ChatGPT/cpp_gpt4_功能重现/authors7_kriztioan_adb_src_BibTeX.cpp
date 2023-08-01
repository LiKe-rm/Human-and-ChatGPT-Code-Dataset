#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <regex>
#include <fstream>

namespace Coders {
    std::string URLEncode(const std::string &value);
    std::string LaTeXDecode(const std::string &value);
}

class BibTeX {
public:
    struct Record {
        std::string type;
        std::string citationKey;
        std::map<std::string, std::string> fields;
    };

    static std::string formatAuthors(const std::string &authorsStr);
    static std::string formatKeywords(const std::string &keywordsStr);
    static Record parseRecord(const std::string &bibtexStr);
    static std::string exportRecord(const Record &record);

private:
    static std::vector<std::string> split(const std::string &str, char delimiter);
};

std::string Coders::URLEncode(const std::string &value) {
    // Implement URLEncode function here
}

std::string Coders::LaTeXDecode(const std::string &value) {
    // Implement LaTeXDecode function here
}

std::string BibTeX::formatAuthors(const std::string &authorsStr) {
    std::vector<std::string> authors = split(authorsStr, ';');
    std::string result;

    for (size_t i = 0; i < authors.size(); ++i) {
        std::string author = authors[i];
        std::string decodedAuthor = Coders::LaTeXDecode(author);
        result += decodedAuthor;

        if (i < authors.size() - 1) {
            result += ", ";
        }
    }

    return result;
}

std::string BibTeX::formatKeywords(const std::string &keywordsStr) {
    std::vector<std::string> keywords = split(keywordsStr, ';');
    std::string result;

    for (size_t i = 0; i < keywords.size(); ++i) {
        std::string keyword = keywords[i];
        std::string decodedKeyword = Coders::LaTeXDecode(keyword);
        result += decodedKeyword;

        if (i < keywords.size() - 1) {
            result += ", ";
        }
    }

    return result;
}

BibTeX::Record BibTeX::parseRecord(const std::string &bibtexStr) {
    std::regex recordPattern(R"(@(\w+)\{([^,]+),)");
    std::smatch recordMatch;
    std::regex_search(bibtexStr, recordMatch, recordPattern);

    Record record;
    record.type = recordMatch[1];
    record.citationKey = recordMatch[2];

    std::regex fieldPattern(R"((\w+)\s*=\s*\{([^\}]+)\})");
    auto fieldBegin = std::sregex_iterator(bibtexStr.begin(), bibtexStr.end(), fieldPattern);
    auto fieldEnd = std::sregex_iterator();

    for (std::sregex_iterator i = fieldBegin; i != fieldEnd; ++i) {
        std::smatch fieldMatch = *i;
        std::string fieldName = fieldMatch[1];
        std::string fieldValue = fieldMatch[2];
        record.fields[fieldName] = fieldValue;
    }

    return record;
}

std::string BibTeX::exportRecord(const Record &record) {
    std::ostringstream output;
    output << "@" << record.type << "{" << record.citationKey << "," << std::endl;

    for (const auto &field : record.fields) {
        output << "  " << field.first << " = {" << field.second << "}," << std::endl;
    }

 // Remove the trailing comma and add the closing brace
    std::string exportedRecord = output.str();
    size_t lastCommaPos = exportedRecord.find_last_of(',');
    exportedRecord[lastCommaPos] = ' ';
    exportedRecord += "}" + std::endl;

    return exportedRecord;
}

std::vectorstd::string BibTeX::split(const std::string &str, char delimiter) {
    std::vectorstd::string tokens;
    std::istringstream tokenStream(str);
    std::string token;

    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}
