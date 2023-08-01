#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <ctime>
#include <random>

// 假设 Coders::HTML2XML 和 Coders::LaTeXDecode 已经包含在这里
namespace Coders {
    std::string HTML2XML(const std::string &html);
    std::string LaTeXDecode(const std::string &latex);
}

class MSWord {
public:
    std::string Export(const std::vector<std::string> &records);
    std::string Header();
    std::string Footer();
    std::string GUIDCreate();

private:
    std::unordered_map<std::string, std::string> types = {
        {"journal", "期刊文章"},
        {"conference", "会议论文"},
        {"book", "图书"},
        {"thesis", "学位论文"},
        {"patent", "专利"}
    };

    std::string parseAuthorOrEditor(const std::string &input);
};

std::string MSWord::Export(const std::vector<std::string> &records) {
    std::stringstream output;
    output << Header();

    for (const std::string &record : records) {
        // 提取记录的类型和标题
        std::string type = ""; // 从 record 中提取文章类型
        std::string title = ""; // 从 record 中提取文章标题

        // 生成 GUID
        std::string guid = GUIDCreate();

        // 输出文章信息
        output << guid << std::endl;
        output << "类型: " << types[type] << std::endl;
        output << "标题: " << Coders::HTML2XML(title) << std::endl;

        // 解析作者和编辑者
        std::string authors = ""; // 从 record 中提取作者信息
        std::string editors = ""; // 从 record 中提取编辑者信息

        output << "作者: " << parseAuthorOrEditor(authors) << std::endl;
        output << "编辑者: " << parseAuthorOrEditor(editors) << std::endl;

        // 输出特定文章类型的信息
        if (type == "journal") {
            // 输出期刊文章特有的信息，如期刊名称、卷、期等
        } else if (type == "conference") {
            // 输出会议论文特有的信息，如会议名称、地点等
        } else if (type == "book") {
            // 输出图书特有的信息，如出版社、出版年份等
        } else if (type == "thesis") {
            // 输出学位论文特有的信息，如学位类型、授予单位等
        } else if (type == "patent") {
            // 输出专利特有的信息，如专利号、申请日期等
        }
    }

    output << Footer();
    return output.str();
}

std::string MSWord::Header() {
    return "Microsoft Word 文献管理格式\n\n";
}

std::string MSWord::Footer() {
    return "\n导出完成";
}

std::string MSWord::GUIDCreate() {
    // 使用随机数生成器生成 GUID
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);
    std::stringstream guid;
    
    for (int i = 0; i < 32; ++i) {
        if (i == 8 || i == 12 || i == 16 || i == 20) {
            guid << "-";
        }
        guid << std::hex << dis(gen);
    }

    return guid.str();
}

std::string MSWord::parseAuthorOrEditor(const std::string &input) {
    // 以分号分隔作者或编辑者
    std::stringstream ss(input);
    std::string name;
    std::vector<std::string> names;

    while (std::getline(ss, name, ';')) {
        names.push_back(Coders::LaTeXDecode(name));
    }

    std::string output;
    for (size_t i = 0; i < names.size(); ++i) {
        output += names[i];
        if (i != names.size() - 1) {
            output += ", ";
        }
    }

    return output;
}

int main() {
    MSWord msword;
    std::vector<std::string> records = {/* 填写记录数据 */};

    std::string exported_data = msword.Export(records);
    std::cout << exported_data << std::endl;

    return 0;
}

