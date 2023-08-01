#include <iostream>
#include <string>
#include <vector>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/aes.h>
#include <openssl/err.h>

class AESCryptor {
public:
    AESCryptor() : ctx(nullptr) {
    }

    ~AESCryptor() {
        EVP_CIPHER_CTX_free(ctx);
    }

    bool init(const std::string &password, const std::string &salt) {
        if (password.empty() || salt.empty()) {
            std::cerr << "Error: empty password or salt." << std::endl;
            return false;
        }

        unsigned char key[EVP_MAX_KEY_LENGTH] = {0};
        unsigned char iv[EVP_MAX_IV_LENGTH] = {0};

        if (!EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha256(), (unsigned char *)salt.c_str(),
                            (unsigned char *)password.c_str(), password.length(), 1, key, iv)) {
            std::cerr << "Error: unable to derive key and IV from password and salt." << std::endl;
            return false;
        }

        ctx = EVP_CIPHER_CTX_new();
        if (ctx == nullptr) {
            std::cerr << "Error: unable to allocate memory for EVP_CIPHER_CTX." << std::endl;
            return false;
        }

        EVP_CIPHER_CTX_init(ctx);
        EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv);

        return true;
    }

    std::vector<unsigned char> update(const std::vector<unsigned char> &data, bool encrypt) {
        int blockSize = EVP_CIPHER_CTX_block_size(ctx);
        int outLen = data.size() + blockSize;
        std::vector<unsigned char> output(outLen);

        int finalLen = 0;
        if (encrypt) {
            EVP_EncryptUpdate(ctx, output.data(), &outLen, data.data(), data.size());
            EVP_EncryptFinal_ex(ctx, output.data() + outLen, &finalLen);
        } else {
            EVP_DecryptUpdate(ctx, output.data(), &outLen, data.data(), data.size());
            EVP_DecryptFinal_ex(ctx, output.data() + outLen, &finalLen);
        }

        output.resize(outLen + finalLen);
        return output;
    }

private:
    EVP_CIPHER_CTX *ctx;
};

int main() {
    std::string password = "mypassword";
    std::string salt = "mysalt";
    std::vector<unsigned char> data = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

    AESCryptor cryptor;
    if (!cryptor.init(password, salt)) {
        return 1;
    }

    std::vector<unsigned char> encryptedData = cryptor.update(data, true);
    std::vector<unsigned char> decryptedData = cryptor.update(encryptedData, false);

    std::cout << "Original data: ";
    for (auto byte : data) {
        std::cout << std::hex << (int)byte << " ";
    }
    std::cout << std::endl;

    std::cout << "Encrypted data: ";
    for (auto byte : encryptedData) {
        std::cout << std::hex << (int)byte << " ";
    }
    std::cout << std::endl;

    std::cout << "Decrypted data: ";
    for (auto byte : decryptedData) {
        std::cout << std::hex << (int)byte << " ";
    }
    std::cout << std::endl;

    // Verify if the decrypted data is the same as the original data
    if (data == decryptedData) {
        std::cout << "The decrypted data matches the original data." << std::endl;
    } else {
        std::cout << "The decrypted data does not match the original data." << std::endl;
    }

    return 0;
}

