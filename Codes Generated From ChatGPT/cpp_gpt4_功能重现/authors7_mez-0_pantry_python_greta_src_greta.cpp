#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <stdexcept>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <Windows.h>

struct GRETA {
    bool error;
    std::string errorMessage;
    std::vector<uint8_t> payload;
    std::vector<uint8_t> decryptedData;
};

using FnPtr = uintptr_t(*)(const char*);

FnPtr parseFunctionAddress(const char* functionName);
std::vector<uint8_t> decryptAES256CBC(const std::vector<uint8_t>& ciphertext,
                                      const std::vector<uint8_t>& key,
                                      const std::vector<uint8_t>& iv);
uint64_t computeFNVHash(const std::string& input);
bool compareHashValues(uint64_t hash1, uint64_t hash2);
std::vector<uint8_t> getKeyFromEnvironment(const std::string& envVar);
std::vector<uint8_t> getKeyFromRegistry(const std::string& regPath, const std::string& regKey);
GRETA* decryptPayload(GRETA* greta);

FnPtr parseFunctionAddress(const char* functionName) {
    return reinterpret_cast<FnPtr>(GetProcAddress(GetModuleHandle(NULL), functionName));
}

std::vector<uint8_t> decryptAES256CBC(const std::vector<uint8_t>& ciphertext,
                                      const std::vector<uint8_t>& key,
                                      const std::vector<uint8_t>& iv) {
    std::vector<uint8_t> plaintext(ciphertext.size());
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    if (!ctx || EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key.data(), iv.data()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Error initializing decryption context");
    }

    int len;
    if (EVP_DecryptUpdate(ctx, plaintext.data(), &len, ciphertext.data(), ciphertext.size()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Error decrypting data");
    }

    int plaintextLen = len;
    if (EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Error finalizing decryption");
    }
    plaintextLen += len;
    plaintext.resize(plaintextLen);

    EVP_CIPHER_CTX_free(ctx);
    return plaintext;
}

uint64_t computeFNVHash(const std::string& input) {
    const uint64_t FNV_prime = 1099511628211ULL;
    const uint64_t FNV_offset_basis = 14695981039346656037ULL;

    uint64_t hash = FNV_offset_basis;
    for (const auto& ch : input) {
        hash ^= ch;
        hash *= FNV_prime;
    }

    return hash;
}

bool compareHashValues(uint64_t hash1, uint64_t hash2) {
    return hash1 == hash2;
}

std::vector<uint8_t> getKeyFromEnvironment(const std::string& envVar) {
    std::vector<uint8_t> key;
    char* envValue = getenv(envVar.c_str());
    if (envValue) {
        std::string keyValue(envValue);
        key.assign(keyValue.begin(), keyValue.end());
    }
    return key;
}

std::vector<uint8_t> getKeyFromRegistry(const std::string& regPath, const std::string& regKey) {
    std::vector<uint8_t> key;
    HKEY hKey;
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, regPath.c_str(), 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        DWORD dataType;
        DWORD dataSize;
        if (RegQueryValueExA(hKey, regKey.c_str(), NULL, &dataType, NULL, &dataSize) == ERROR_SUCCESS) {
            if (dataType == REG_BINARY || dataType == REG_SZ) {
                key.resize(dataSize);
                RegQueryValueExA(hKey, regKey.c_str(), NULL, &dataType, key.data(), &dataSize);
            }
        }
        RegCloseKey(hKey);
    }
    return key;
}

GRETA* decryptPayload(GRETA* greta) {
    try {
        std::vector<uint8_t> key = getKeyFromEnvironment("KEY_ENV_VAR");
        if (key.empty()) {
            key = getKeyFromRegistry("SOFTWARE\MY_APP", "KEY_REG_VALUE");
        }
        if (key.empty()) {
            throw std::runtime_error("Error: Unable to find key");
        }
        uint64_t hash = computeFNVHash("expectedHash");
        if (!compareHashValues(hash, computeFNVHash(std::string(key.begin(), key.end())))) {
            throw std::runtime_error("Error: Key hash mismatch");
        }
        std::vector<uint8_t> iv(greta->payload.begin(), greta->payload.begin() + 16);
        std::vector<uint8_t> ciphertext(greta->payload.begin() + 16, greta->payload.end());
        greta->decryptedData = decryptAES256CBC(ciphertext, key, iv);
        greta->error = false;
    } catch (const std::runtime_error& e) {
        greta->error = true;
        greta->errorMessage = e.what();
    }
    return greta;
}

