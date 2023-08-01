#include <iostream>
#include <mysql.h>
#include <stdexcept>

class CDBCmd {
public:
    CDBCmd();
    ~CDBCmd();

    void Init(MYSQL *mysql);
    void Close();
    void Open(const std::string &query);
    void MoveFirst();
    bool MoveNext();
    void SetQuery(const std::string &query);
    void Update(const std::string &query);
    template<typename T>
    T GetRec(int fieldIndex);
    int FindField(const std::string &fieldName);

private:
    MYSQL *m_mysql;
    MYSQL_RES *m_result;
    MYSQL_ROW m_row;
};

CDBCmd::CDBCmd() : m_mysql(nullptr), m_result(nullptr), m_row(nullptr) {}

CDBCmd::~CDBCmd() {
    Close();
}

void CDBCmd::Init(MYSQL *mysql) {
    m_mysql = mysql;
}

void CDBCmd::Close() {
    if (m_result) {
        mysql_free_result(m_result);
        m_result = nullptr;
    }
}

void CDBCmd::Open(const std::string &query) {
    if (!m_mysql) {
        throw std::runtime_error("CDBCmd not initialized");
    }

    if (mysql_query(m_mysql, query.c_str())) {
        throw std::runtime_error(mysql_error(m_mysql));
    }

    m_result = mysql_store_result(m_mysql);
}

void CDBCmd::MoveFirst() {
    if (!m_result) {
        throw std::runtime_error("No query result available");
    }
    mysql_data_seek(m_result, 0);
    m_row = mysql_fetch_row(m_result);
}

bool CDBCmd::MoveNext() {
    if (!m_result) {
        throw std::runtime_error("No query result available");
    }
    m_row = mysql_fetch_row(m_result);
    return m_row != nullptr;
}

void CDBCmd::SetQuery(const std::string &query) {
    Close();
    Open(query);
}

void CDBCmd::Update(const std::string &query) {
    if (!m_mysql) {
        throw std::runtime_error("CDBCmd not initialized");
    }

    if (mysql_query(m_mysql, query.c_str())) {
        throw std::runtime_error(mysql_error(m_mysql));
    }
}

template<>
int CDBCmd::GetRec<int>(int fieldIndex) {
    if (!m_row) {
        throw std::runtime_error("No record available");
    }
    return std::stoi(m_row[fieldIndex]);
}

template<>
std::string CDBCmd::GetRec<std::string>(int fieldIndex) {
    if (!m_row) {
        throw std::runtime_error("No record available");
    }
    return m_row[fieldIndex];
}

int CDBCmd::FindField(const std::string &fieldName) {
    if (!m_result) {
        throw std::runtime_error("No query result available");
    }
    MYSQL_FIELD *fields = mysql_fetch_fields(m_result);
    int numFields = mysql_num_fields(m_result);

    for (int i = 0; i < numFields; i++) {
        if (fieldName == fields[i].name) {
            return i;
        }
    }
    return -1;
}
