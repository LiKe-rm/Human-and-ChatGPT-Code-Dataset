// $Id$

#include "CKTCPConnection.h"

// 构造函数
CKTCPConnection::CKTCPConnection() : CKBufferedSocket() {
    m_bConnected = false;
}

// 析构函数
CKTCPConnection::~CKTCPConnection() {
    Disconnect();
}

// 连接到指定的地址和端口
bool CKTCPConnection::Connect(const std::string& strAddress, int nPort) {
    // 如果已经连接，则返回 false
    if (m_bConnected) {
        return false;
    }
    
    // 创建 socket
    if (!Create()) {
        return false;
    }
    
    // 连接到指定地址和端口
    if (!ConnectHelper(strAddress, nPort)) {
        Close();
        return false;
    }
    
    // 连接成功
    m_bConnected = true;
    return true;
}

// 断开连接
void CKTCPConnection::Disconnect() {
    if (m_bConnected) {
        Close();
        m_bConnected = false;
    }
}

// 检查连接是否建立
bool CKTCPConnection::IsConnected() const {
    return m_bConnected;
}

// 从套接字读取指定数量的字节
bool CKTCPConnection::Read(void* pBuffer, size_t nBytes) {
    if (!IsConnected()) {
        return false;
    }
    
    return CKBufferedSocket::Read(pBuffer, nBytes);
}

// 将指定数量的字节写入套接字
bool CKTCPConnection::Write(const void* pBuffer, size_t nBytes) {
    if (!IsConnected()) {
        return false;
    }
    
    return CKBufferedSocket::Write(pBuffer, nBytes);
}

// 检查两个连接是否相等
bool CKTCPConnection::operator==(const CKTCPConnection& other) const {
    return (this == &other);
}
