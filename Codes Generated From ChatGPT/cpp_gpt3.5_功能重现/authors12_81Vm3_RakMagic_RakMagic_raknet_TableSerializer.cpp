#include <iostream>
#include <vector>
#include <cstring>
#include "RakNet/BitStream.h"
#include "RakNet/StringCompressor.h"
#include "RakNet/BitStreamAligned.h"

using namespace RakNet;

// �Զ�������ݽṹ��ʾ���ݱ��е���
struct TableColumn {
    std::string name;
    int type;
};

// �Զ�������ݽṹ��ʾ���ݱ��е���
struct TableRow {
    std::vector<std::string> data;
};

class DataTableSerializer {
    public:
        // �����ݱ����Ϣ���л���һ��λ����
    static void SerializeTable(BitStream& stream, const std::vector<TableColumn>& columns, const std::vector<TableRow>& rows) {
        // ���л��е�����
        stream.WriteCompressed(columns.size());

        // ���л�ÿһ�е���Ϣ
        for (const auto& column : columns) {
            // ���л�����
            StringCompressor::Instance()->EncodeString(column.name.c_str(), column.name.length() + 1, &stream);

            // ���л�������
            stream.Write(column.type);
        }

        // ���л��е�����
        stream.WriteCompressed(rows.size());

        // ���л�ÿһ�е���Ϣ
        for (const auto& row : rows) {
            // ���л�ÿһ�е�����
            for (const auto& data : row.data) {
                // ���л������ַ���
                StringCompressor::Instance()->EncodeString(data.c_str(), data.length() + 1, &stream);
            }
        }
    }

    // ��һ�������л����ݱ���Ϣ���ɵ��ֽ������з����л����ݱ���Ϣ
    static void DeserializeTable(BitStream& stream, std::vector<TableColumn>& columns, std::vector<TableRow>& rows) {
        // �����л��е�����
        uint32_t columnCount;
        stream.ReadCompressed(columnCount);

        // �����л�ÿһ�е���Ϣ
        for (uint32_t i = 0; i < columnCount; i++) {
            TableColumn column;

            // �����л�����
            char name[256];
            StringCompressor::Instance()->DecodeString(name, 256, &stream);
            column.name = name;

            // �����л�������
            stream.Read(column.type);

            columns.push_back(column);
        }

        // �����л��е�����
        uint32_t rowCount;
        stream.ReadCompressed(rowCount);

        // �����л�ÿһ�е���Ϣ
        for (uint32_t i = 0; i < rowCount; i++) {
            TableRow row;

            // �����л�ÿһ�е�����
            for (uint32_t j = 0; j < columnCount; j++) {
                char data[256];
                StringCompressor::Instance()->DecodeString(data, 256, &stream);
                row.data.push_back(data);
            }

            rows.push_back(row);
        }
    }

    // �����ݱ��е���Ϣ���л���һ��λ����
    static void SerializeRow(BitStream& stream, const std::vector<std::string>&const std::vector<TableColumn>& columns, const TableRow& row) {
// ���л�ÿһ�е�����
        for (uint32_t i = 0; i < columns.size(); i++) {
        // ���л������ַ���
            StringCompressor::Instance()->EncodeString(row.data[i].c_str(), row.data[i].length() + 1, &stream);
        }
    }
    // ��λ���з����л����ݱ�����Ϣ
    static void DeserializeRow(BitStream& stream, const std::vector<TableColumn>& columns, TableRow& row) {
        // �����л�ÿһ�е�����
        for (uint32_t i = 0; i < columns.size(); i++) {
            char data[256];
            StringCompressor::Instance()->DecodeString(data, 256, &stream);
            row.data.push_back(data);
        }
    }
};

int main() {
// ���Դ���
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
    // ���л����ݱ�
    DataTableSerializer::SerializeTable(stream, columns, rows);

    // �����л����ݱ�
    std::vector<TableColumn> desColumns;
    std::vector<TableRow> desRows;
    DataTableSerializer::DeserializeTable(stream, desColumns, desRows);

    // ��鷴���л������ݱ��Ƿ���ԭʼ���ݱ���ͬ
    if (columns == desColumns && rows == desRows) {
        std::cout << "Serialization and deserialization succeeded!\n";
    } else {
        std::cout << "Serialization and deserialization failed!\n";
    }

    return 0;
}