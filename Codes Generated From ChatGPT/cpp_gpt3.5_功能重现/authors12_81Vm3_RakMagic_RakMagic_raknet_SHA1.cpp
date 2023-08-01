#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <cstdint>

class CSHA1
{
    public:
    CSHA1();
    ~CSHA1();
    void Reset();
    void Transform(const unsigned char* pBuffer);
    void Update(const unsigned char* pData, unsigned int uLen);
    void Update(const char* pData, unsigned int uLen);
    bool HashFile(const char* pszFileName);
    void Final();
    void ReportHash(unsigned char* pHash);
    void GetHash(unsigned char* pHash);
    unsigned char* GetHash();

    private:
    uint32_t m_state[5];
    uint32_t m_count[2];
    unsigned char m_buffer[64];

    void SHA1Transform(uint32_t state[5], const unsigned char buffer[64]);
    void SHA1ProcessMessageBlock(const unsigned char* pData);
};

CSHA1::CSHA1()
{
    Reset();
}

CSHA1::~CSHA1()
{
    // Clear sensitive information from memory
    memset(m_state, 0, sizeof(m_state));
    memset(m_count, 0, sizeof(m_count));
    memset(m_buffer, 0, sizeof(m_buffer));
}

void CSHA1::Reset()
{
    m_state[0] = 0x67452301;
    m_state[1] = 0xEFCDAB89;
    m_state[2] = 0x98BADCFE;
    m_state[3] = 0x10325476;
    m_state[4] = 0xC3D2E1F0;

    m_count[0] = 0;
    m_count[1] = 0;
}

void CSHA1::Transform(const unsigned char* pBuffer)
{
    SHA1Transform(m_state, pBuffer);
}

void CSHA1::Update(const unsigned char* pData, unsigned int uLen)
{
    uint32_t i = 0;

    for (i = 0; i < uLen; i++)
    {
        m_buffer[m_count[0] & 63] = pData[i];
        m_count[0]++;
        if (m_count[0] == 0)
        {
            m_count[1]++;
        }
        if ((m_count[0] & 63) == 0)
        {
            SHA1ProcessMessageBlock(m_buffer);
        }
    }
}

void CSHA1::Update(const char* pData, unsigned int uLen)
{
    Update(reinterpret_cast<const unsigned char*>(pData), uLen);
}

bool CSHA1::HashFile(const char* pszFileName)
{
    std::ifstream file(pszFileName, std::ios::binary);
    if (!file.is_open())
    {
        return false;
    }

    char buffer[1024];
    while (file.good())
    {
        file.read(buffer, sizeof(buffer));
        Update(buffer, static_cast<unsigned int>(file.gcount()));
    }

    Final();

    return true;
}

void CSHA1::Final()
{
    unsigned char finalcount[8];
    unsigned char c;
    uint32_t i;

    for (i = 0; i < 8; i++)
    {
        finalcount[i] = static_cast<unsigned char>((m_count[(i >= 4 ? 0 : 1)] >> ((3 - (i & 3)) * 8)) & 255);
    }
    c = 0x80;
    Update(&c, 1);

    while ((m_count[0] & 63) != 56)
    {
        c = 0x00;
        Update(&c, 1);
    }

    Update(finalcount, 8);

    for (i = 0; i < 20; i++)
    {
        finalcount[i] = static_cast<unsigned char>((m_state[i >> 2] >> ((3 - (i & 3)) * 8)) & 255);
    }

    ReportHash(finalcount);
}

void CSHA1::ReportHash(unsigned char* pHash)
{
    std::cout << "SHA-1 hash: ";
    for (int i = 0; i < 20; i++)
    {
        std::cout << std::hex << static_cast<int>(pHash[i]);
    }
    std::cout << std::dec << std::endl;
}

void CSHA1::GetHash(unsigned char* pHash)
{
    std::memcpy(pHash, m_state, 20);
}

unsigned char* CSHA1::GetHash()
{
    return reinterpret_cast<unsigned char*>(m_state);
}

void CSHA1::SHA1Transform(uint32_t state[5], const unsigned char buffer[64])
{
    uint32_t a, b, c, d, e;
    uint32_t i, j, t;
    uint32_t x[16];
    for (i = 0, j = 0; i < 16; ++i, j += 4)
    {
        x[i] = (buffer[j] << 24) | (buffer[j + 1] << 16) | (buffer[j + 2] << 8) | (buffer[j + 3]);
    }

    for (; i < 80; ++i)
    {
        x[i] = x[i - 3] ^ x[i - 8] ^ x[i - 14] ^ x[i - 16];
        x[i] = (x[i] << 1) | (x[i] >> 31);
    }

    a = state[0];
    b = state[1];
    c = state[2];
    d = state[3];
    e = state[4];

    for (i = 0; i < 20; ++i)
    {
        t = (a << 5) | (a >> 27);
        t += ((b & c) | ((~b) & d)) + e + x[i] + 0x5A827999;
        e = d;
        d = c;
        c = (b << 30) | (b >> 2);
        b = a;
        a = t;
    }

    for (; i < 40; ++i)
    {
        t = (a << 5) | (a >> 27);
        t += (b ^ c ^ d) + e + x[i] + 0x6ED9EBA1;
        e = d;
        d = c;
        c = (b << 30) | (b >> 2);
        b = a;
        a = t;
    }

    for (; i < 60; ++i)
    {
        t = (a << 5) | (a >> 27);
        t += ((b & c) | (b & d) | (c & d)) + e + x[i] + 0x8F1BBCDC;
        e = d;
        d = c;
        c = (b << 30) | (b2);
        b = a;
        a = t;
    }
    for (; i < 80; ++i)
    {
        t = (a << 5) | (a >> 27);
        t += (b ^ c ^ d) + e + x[i] + 0xCA62C1D6;
        e = d;
        d = c;
        c = (b << 30) | (b >> 2);
        b = a;
        a = t;
    }

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
}

void CSHA1::SHA1ProcessMessageBlock(const unsigned char* pData)
{
    uint32_t temp;
    uint32_t W[80];
    uint32_t A, B, C, D, E;
    for (int i = 0; i < 16; i++)
    {
        W[i] = ((uint32_t)pData[i * 4] << 24) | ((uint32_t)pData[i * 4 + 1] << 16) |
            ((uint32_t)pData[i * 4 + 2] << 8) | ((uint32_t)pData[i * 4 + 3]);
    }

    for (int i = 16; i < 80; i++)
    {
        W[i] = W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16];
        W[i] = (W[i] << 1) | (W[i] >> 31);
    }

    A = m_state[0];
    B = m_state[1];
    C = m_state[2];
    D = m_state[3];
    E = m_state[4];

    for (int i = 0; i < 20; i++)
    {
        temp = ((A << 5) | (A >> 27)) + ((B & C) | ((~B) & D)) + E + W[i] + 0x5A827999;
        E = D;
        D = C;
        C = (B << 30) | (B >> 2);
        B = A;
        A = temp;
    }

    for (int i = 20; i < 40; i++)
    {
        temp = ((A << 5) | (A >> 27)) + (B ^ C ^ D) + E + W[i] + 0x6ED9EBA1;
        E = D;
        D = C;
        C = (B << 30) | (B >> 2);
        B = A;
        A = temp;
    }

    for (int i = 40; i < 60; i++)
    {
        temp = ((A << 5) | (A >> 27)) + ((B & C) | (B & D) | (C & D)) + E + W[i] + 0x8F1BBCDC;
        E = D;
        D = C;
        C = (B << 30) | (B >> 2);
        B = A;
        A = temp;
    }

    for (int i = 60; i < 80; i++)
    {
        temp = ((A << 5) | (A >> 27)) + (B ^ C ^ D) + E + W[i] + 0xCA62C1D6;
        E= D;
        D = C;
        C = (B << 30) | (B >> 2);
        B = A;
        A = temp;
    }
    m_state[0] += A;
    m_state[1] += B;
    m_state[2] += C;
    m_state[3] += D;
    m_state[4] += E;
}

int main()
{
    CSHA1 sha1;
    const char* pData = "This is a test message.";
    unsigned char hash[20];
    sha1.Update(reinterpret_cast<const unsigned char*>(pData), static_cast<unsigned int>(strlen(pData)));
    sha1.Final();
    sha1.ReportHash(hash);

    sha1.Reset();
    sha1.HashFile("test.txt");
    sha1.ReportHash(hash);

    return 0;
}