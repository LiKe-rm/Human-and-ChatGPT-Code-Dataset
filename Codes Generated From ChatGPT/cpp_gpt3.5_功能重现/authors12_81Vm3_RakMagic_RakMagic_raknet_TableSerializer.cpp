#include <iostream>
#include <vector>
#include <cstring>
#include "RakNet/BitStream.h"
#include "RakNet/StringCompressor.h"
#include "RakNet/BitStreamAligned.h"

using namespace RakNet;

// 自定义的数据结构表示数据表中的列
struct TableColumn {
    std::string name;
    int type;
};

// 自定义的数据结构表示数据表中的行
struct TableRow {
    std::vector<std::string> data;
};

class DataTableSerializer {
    public:
        // 将数据表的信息序列化到一个位流中
    static void SerializeTable(BitStream& stream, const std::vector<TableColumn>& columns, const std::vector<TableRow>& rows) {
        // 序列化列的数量
        stream.WriteCompressed(columns.size());

        // 序列化每一列的信息
        for (const auto& column : columns) {
            // 序列化列名
            StringCompressor::Instance()->EncodeString(column.name.c_str(), column.name.length() + 1, &stream);

            // 序列化列类型
            stream.Write(column.type);
        }

        // 序列化行的数量
        stream.WriteCompressed(rows.size());

        // 序列化每一行的信息
        for (const auto& row : rows) {
            // 序列化每一列的数据
            for (const auto& data : row.data) {
                // 序列化数据字符串
                StringCompressor::Instance()->EncodeString(data.c_str(), data.length() + 1, &stream);
            }
        }
    }

    // 从一个由序列化数据表信息构成的字节数组中反序列化数据表信息
    static void DeserializeTable(BitStream& stream, std::vector<TableColumn>& columns, std::vector<TableRow>& rows) {
        // 反序列化列的数量
        uint32_t columnCount;
        stream.ReadCompressed(columnCount);

        // 反序列化每一列的信息
        for (uint32_t i = 0; i < columnCount; i++) {
            TableColumn column;

            // 反序列化列名
            char name[256];
            StringCompressor::Instance()->DecodeString(name, 256, &stream);
            column.name = name;

            // 反序列化列类型
            stream.Read(column.type);

            columns.push_back(column);
        }

        // 反序列化行的数量
        uint32_t rowCount;
        stream.ReadCompressed(rowCount);

        // 反序列化每一行的信息
        for (uint32_t i = 0; i < rowCount; i++) {
            TableRow row;

            // 反序列化每一列的数据
            for (uint32_t j = 0; j < columnCount; j++) {
                char data[256];
                StringCompressor::Instance()->DecodeString(data, 256, &stream);
                row.data.push_back(data);
            }

            rows.push_back(row);
        }
    }

    // 将数据表行的信息序列化到一个位流中
    static void SerializeRow(BitStream& stream, const std::vector<std::string>&const std::vector<TableColumn>& columns, const TableRow& row) {
// 序列化每一列的数据
        for (uint32_t i = 0; i < columns.size(); i++) {
        // 序列化数据字符串
            StringCompressor::Instance()->EncodeString(row.data[i].c_str(), row.data[i].length() + 1, &stream);
        }
    }
    // 从位流中反序列化数据表行信息
    static void DeserializeRow(BitStream& stream, const std::vector<TableColumn>& columns, TableRow& row) {
        // 反序列化每一列的数据
        for (uint32_t i = 0; i < columns.size(); i++) {
            char data[256];
            StringCompressor::Instance()->DecodeString(data, 256, &stream);
            row.data.push_back(data);
        }
    }
};

int main() {
// 测试代码
    BitStream stream;
    std::vector<TableColumn> columns ={
    {"Name", 0},
    {"Age", 1},
    {"Gender", 0}
    };
    std::vector<TableRow> rows ={
    {{"Alice", "20", "Female"}},
    {{"Bob", "25", "Male"}},
    {{"Charlie", "30", "Male"}}
    };
    // 序列化数据表
    DataTableSerializer::SerializeTable(stream, columns, rows);

    // 反序列化数据表
    std::vector<TableColumn> desColumns;
    std::vector<TableRow> desRows;
    DataTableSerializer::DeserializeTable(stream, desColumns, desRows);

    // 检查反序列化的数据表是否与原始数据表相同
    if (columns == desColumns && rows == desRows) {
        std::cout << "Serialization and deserialization succeeded!\n";
    } else {
        std::cout << "Serialization and deserialization failed!\n";
    }

    return 0;
}