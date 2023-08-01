#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define BUFSIZE 1024

class CKSMTPDelivery {
public:
    CKSMTPDelivery() {
        mHostname = "";
        mFromEMailAddress = "";
        mHostConnection = NULL;
    }
    
    CKSMTPDelivery(const std::string& hostname) {
        mHostname = hostname;
        mFromEMailAddress = "";
        mHostConnection = NULL;
    }
    
    CKSMTPDelivery(const std::string& hostname, const std::string& fromEmailAddress) {
        mHostname = hostname;
        mFromEMailAddress = fromEmailAddress;
        mHostConnection = NULL;
    }
    
    CKSMTPDelivery(const CKSMTPDelivery& other) {
        mHostname = other.mHostname;
        mFromEMailAddress = other.mFromEMailAddress;
        mHostConnection = other.mHostConnection;
    }
    
    ~CKSMTPDelivery() {
        disconnect();
    }
    
    CKSMTPDelivery& operator=(const CKSMTPDelivery& other) {
        if (this != &other) {
            mHostname = other.mHostname;
            mFromEMailAddress = other.mFromEMailAddress;
            mHostConnection = other.mHostConnection;
        }
        return *this;
    }
    
    bool checkServerAvailable() {
        int sockfd;
        struct addrinfo hints, *servinfo, *p;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        if (getaddrinfo(mHostname.c_str(), "smtp", &hints, &servinfo) != 0) {
            return false;
        }
        for (p = servinfo; p != NULL; p = p->ai_next) {
            if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
                continue;
            }
            if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
                close(sockfd);
                continue;
            }
            break;
        }
        freeaddrinfo(servinfo);
        if (p == NULL) {
            return false;
        }
        mHostConnection = fdopen(sockfd, "r+");
        char buffer[BUFSIZE];
        if (fgets(buffer, BUFSIZE, mHostConnection) == NULL) {
            return false;
        }
        if (strncmp(buffer, "220", 3) != 0) {
            return false;
        }
        return true;
    }
    
    bool sendEmail(const std::string& toEmailAddress, const std::string& subject, const std::string& messageBody) {
        if (mHostConnection == NULL) {
            return false;
        }
        if (mFromEMailAddress == "") {
            return false;
        }
        std::string currentTimeString = getCurrentTimeString();
        std::string mailFromCommand = "MAIL FROM:<" + mFromEMailAddress + ">\r\n";
        std::string rcptToCommand = "RCPT TO:<" + toEmailAddress + ">\r\n";
        std::string dataCommand = "DATA\r\n";
        std::string subjectHeader = "Subject: " + subject + "\r\n";
        std::string dateHeader = "Date: " + currentTimeString + "\r\n";
       
    std::string fromHeader = "From: <" + mFromEMailAddress + ">\r\n";
    std::string toHeader = "To: <" + toEmailAddress + ">\r\n";
    std::string messageBodyHeader = "\r\n" + messageBody + "\r\n";
    std::string mailMessage = subjectHeader + dateHeader + fromHeader + toHeader + messageBodyHeader + ".\r\n";
    if (fputs(mailFromCommand.c_str(), mHostConnection) == EOF) {
        return false;
    }
    if (fgets(buffer, BUFSIZE, mHostConnection) == NULL) {
        return false;
    }
    if (strncmp(buffer, "250", 3) != 0) {
        return false;
    }
    if (fputs(rcptToCommand.c_str(), mHostConnection) == EOF) {
        return false;
    }
    if (fgets(buffer, BUFSIZE, mHostConnection) == NULL) {
        return false;
    }
    if (strncmp(buffer, "250", 3) != 0) {
        return false;
    }
    if (fputs(dataCommand.c_str(), mHostConnection) == EOF) {
        return false;
    }
    if (fgets(buffer, BUFSIZE, mHostConnection) == NULL) {
        return false;
    }
    if (strncmp(buffer, "354", 3) != 0) {
        return false;
    }
    if (fputs(mailMessage.c_str(), mHostConnection) == EOF) {
        return false;
    }
    if (fgets(buffer, BUFSIZE, mHostConnection) == NULL) {
        return false;
    }
    if (strncmp(buffer, "250", 3) != 0) {
        return false;
    }
    return true;
}

std::string getCurrentTimeString() {
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 80, "%a, %d %b %Y %H:%M:%S %z", timeinfo);
    return std::string(buffer);
}

bool operator==(const CKSMTPDelivery& other) const {
    return mHostname == other.mHostname && mFromEMailAddress == other.mFromEMailAddress && mHostConnection == other.mHostConnection;
}

bool operator!=(const CKSMTPDelivery& other) const {
    return !(*this == other);
}

std::string toString() const {
    return "Hostname: " + mHostname + ", From: " + mFromEMailAddress;
}
private:
std::string mHostname;
std::string mFromEMailAddress;
FILE* mHostConnection;
void disconnect() {
    if (mHostConnection != NULL) {
        fputs("QUIT\r\n", mHostConnection);
        fclose(mHostConnection);
        mHostConnection = NULL;
    }
}
};