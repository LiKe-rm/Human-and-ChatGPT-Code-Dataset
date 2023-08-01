#include <iostream>
#include <cstring>
#include <Windows.h>
#include <bcrypt.h>
#include <wincred.h>
#include <yubihsm.h>

#pragma comment(lib, "bcrypt.lib")
#pragma comment(lib, "credui.lib")
#pragma comment(lib, "yubihsm.lib")

namespace Crypto {
    const int SALT_LENGTH = 16;
    const BYTE SALT_VALUE[] = { 0x4b, 0x89, 0x1f, 0x29, 0x3e, 0x01, 0xa1, 0x75, 0xff, 0x44, 0x2c, 0xf2, 0x6a, 0x86, 0xc7, 0x6d };

    void deriveKey(const char* password, size_t passwordSize, BYTE* key, size_t keySize) {
        BCRYPT_ALG_HANDLE hAlg;
        BCryptOpenAlgorithmProvider(&hAlg, BCRYPT_SHA256_ALGORITHM, nullptr, 0);
        BCryptDeriveKeyPBKDF2(hAlg, (PUCHAR)password, (ULONG)passwordSize, SALT_VALUE, SALT_LENGTH, 1000, key, (ULONG)keySize, 0);
        BCryptCloseAlgorithmProvider(hAlg, 0);
    }

    void encrypt(const BYTE* plain, size_t plainSize, const BYTE* key, size_t keySize, const BYTE* iv, size_t ivSize, BYTE* cipher) {
        BCRYPT_ALG_HANDLE hAlg;
        BCRYPT_KEY_HANDLE hKey;
        BCryptOpenAlgorithmProvider(&hAlg, BCRYPT_AES_ALGORITHM, nullptr, 0);
        BCryptGenerateSymmetricKey(hAlg, &hKey, nullptr, 0, (PUCHAR)key, (ULONG)keySize, 0);
        ULONG cipherSize;
        BCryptEncrypt(hKey, (PUCHAR)plain, (ULONG)plainSize, nullptr, (PUCHAR)iv, (ULONG)ivSize, cipher, (ULONG)plainSize, &cipherSize, 0);
        BCryptDestroyKey(hKey);
        BCryptCloseAlgorithmProvider(hAlg, 0);
    }

    void decrypt(const BYTE* cipher, size_t cipherSize, const BYTE* key, size_t keySize, const BYTE* iv, size_t ivSize, BYTE* plain) {
        BCRYPT_ALG_HANDLE hAlg;
        BCRYPT_KEY_HANDLE hKey;
        BCryptOpenAlgorithmProvider(&hAlg, BCRYPT_AES_ALGORITHM, nullptr, 0);
        BCryptGenerateSymmetricKey(hAlg, &hKey, nullptr, 0, (PUCHAR)key, (ULONG)keySize, 0);
        ULONG plainSize;
        BCryptDecrypt(hKey, (PUCHAR)cipher, (ULONG)cipherSize, nullptr, (PUCHAR)iv, (ULONG)ivSize, plain, (ULONG)cipherSize, &plainSize, 0);
        BCryptDestroyKey(hKey);
        BCryptCloseAlgorithmProvider(hAlg, 0);
    }

    void protect(const BYTE* plain, size_t plainSize, DATA_BLOB* cipher) {
        CRYPTPROTECT_PROMPTSTRUCT prompt = { sizeof(CRYPTPROTECT_PROMPTSTRUCT), 0, nullptr, nullptr, 0, nullptr };
        CRYPTPROTECT_DATA protectData = { (ULONG)plainSize, (PUCHAR)const_cast<BYTE*>(plain), 0, nullptr };
        if (!CryptProtectData(&protectData, L"", nullptr, nullptr, &prompt, 0, cipher)) {
            throw std::runtime_error("Failed to protect data");
        }
    }
    void unprotect(const DATA_BLOB* cipher, BYTE* plain, size_t* plainSize) {
        CRYPTPROTECT_PROMPTSTRUCT prompt = { sizeof(CRYPTPROTECT_PROMPTSTRUCT), 0, nullptr, nullptr, 0, nullptr };
        CRYPTPROTECT_DATA protectData = { cipher->cbData, cipher->pbData, 0, nullptr };
        if (!CryptUnprotectData(&protectData, nullptr, nullptr, nullptr, &prompt, 0, (DATA_BLOB*)plainSize)) {
            throw std::runtime_error("Failed to unprotect data size");
        }
        if (*plainSize > 0) {
            if (!CryptUnprotectData(&protectData, nullptr, nullptr, nullptr, &prompt, 0, (DATA_BLOB*)plainSize)) {
                throw std::runtime_error("Failed to unprotect data content");
            }
        }
    }
}

class Yubi {
public:
    Yubi() {
        yh_init();
        yh_connect(YH_ANY, nullptr, &m_session);
        yh_create_session_derived(m_session, "", "password", strlen("password"), YH_AUTH_PASSWORD, &m_session);
    }
    ~Yubi() {
        yh_disconnect(m_session);
        yh_cleanup();
    }

    int getPinRetries() {
        uint8_t retries;
        yh_get_pin_retries(m_session, 1, &retries);
        return retries;
    }

    void verifyPin(const char* pin) {
        yh_authenticate_session(m_session, 1, (const uint8_t*)pin, strlen(pin));
    }

    void signData(const BYTE* data, size_t dataSize, uint16_t objectId, BYTE* signature, size_t* signatureSize) {
        yh_sign_data(m_session, objectId, data, dataSize, YH_ALGO_RSA_PKCS1_SHA256, YH_UNBLOCKED, signature, signatureSize);
    }

    std::string getDeviceModel() {
        uint32_t deviceType;
        char deviceName[256];
        yh_get_device_info(m_session, &deviceType, nullptr, nullptr, nullptr, nullptr, deviceName, sizeof(deviceName));
        return std::string(deviceName);
    }

    void generateKeyFile(const char* password, const char* filePath) {
        BYTE key[32];
        Crypto::deriveKey(password, strlen(password), key, sizeof(key));

        DATA_BLOB cipher;
        Crypto::protect(key, sizeof(key), &cipher);

        HANDLE hFile = CreateFileA(filePath, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (hFile == INVALID_HANDLE_VALUE) {
            throw std::runtime_error("Failed to create key file");
        }

        DWORD bytesWritten;
        if (!WriteFile(hFile, cipher.pbData, cipher.cbData, &bytesWritten, nullptr)) {
            CloseHandle(hFile);
            throw std::runtime_error("Failed to write key file");
        }

        CloseHandle(hFile);
        LocalFree(cipher.pbData);
    }
private:
    yh_session m_session;
}
