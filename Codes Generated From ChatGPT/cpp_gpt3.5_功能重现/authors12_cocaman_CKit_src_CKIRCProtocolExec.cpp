#include <thread>
#include "CKIRCProtocolExec.h"

CKIRCProtocolExec::CKIRCProtocolExec(CKIRCIncomingMessage* message, CKIRCProtocol* protocol) :
    m_message(message),
    m_protocol(protocol)
{
}

CKIRCProtocolExec::~CKIRCProtocolExec()
{
    delete m_message;
}

void CKIRCProtocolExec::handleMessage(CKIRCIncomingMessage* message, CKIRCProtocol* protocol)
{
    CKIRCProtocolExec* exec = new CKIRCProtocolExec(message, protocol);
    std::thread t(&CKIRCProtocolExec::process, exec);
    t.detach();
}

void CKIRCProtocolExec::process()
{
    m_protocol->processMessage(m_message);
    terminate();
}

void CKIRCProtocolExec::terminate()
{
    delete this;
}

CKIRCIncomingMessage* CKIRCProtocolExec::getMessage() const
{
    return m_message;
}

CKIRCProtocol* CKIRCProtocolExec::getProtocol() const
{
    return m_protocol;
}
