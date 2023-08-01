#include <iostream>
#include <dirent.h>
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

using namespace rapidjson;

int main() {
    DIR* dir = opendir("/path/to/folder");
    dirent* entry;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) { // 如果是普通文件
            FILE* fp = fopen(entry->d_name, "r");
            char buffer[1024];
            FileReadStream is(fp, buffer, sizeof(buffer));
            Document doc;
            doc.ParseStream(is);
            fclose(fp);

            if (doc.HasMember("name")) {
                std::string name = doc["name"].GetString();

                // 创建相应的文件夹
                std::string folder_name = "/path/to/folder/" + name;
                mkdir(folder_name.c_str(), 0777);

                // 将文件移动到对应的文件夹中
                std::string old_path = "/path/to/folder/" + std::string(entry->d_name);
                std::string new_path = folder_name + "/" + std::string(entry->d_name);
                rename(old_path.c_str(), new_path.c_str());
            }
        }
    }

    closedir(dir);
    return 0;
}