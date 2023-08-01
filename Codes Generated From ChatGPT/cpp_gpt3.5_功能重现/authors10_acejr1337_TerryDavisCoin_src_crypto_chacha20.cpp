#include <iostream>
#include <cstring>

class ChaCha20 {
    public:
    ChaCha20(): rounds(20) {}
    ~ChaCha20() {}

    void SetKey(const unsigned char* key, int keylen);
    void SetIV(const unsigned char* iv, int ivlen);
    void Seek(uint64_t pos);
    void Output(const unsigned char* input, unsigned char* output, size_t len);

    private:
    void QuarterRound(uint32_t& a, uint32_t& b, uint32_t& c, uint32_t& d);
    void ChaChaBlock(uint32_t output[16]);
    void ResetCounter();

    uint32_t state[16];
    uint32_t original_state[16];
    uint8_t buffer[64];
    uint32_t buffer_pos;
    uint32_t rounds;
    uint64_t counter;
};

void ChaCha20::SetKey(const unsigned char* key, int keylen) {
    if (keylen != 16 && keylen != 32) {
        throw std::runtime_error("invalid key length");
    }

    // Initialize the state with constants
    state[0] = 0x61707865; // "expa"
    state[1] = 0x3320646e; // "nd 3"
    state[2] = 0x79622d32; // "2-by"
    state[3] = 0x6b206574; // "te k"

    // Set the key
    state[4] = *((uint32_t*)(key));
    state[5] = *((uint32_t*)(key + 4));
    state[6] = *((uint32_t*)(key + 8));
    state[7] = *((uint32_t*)(key + 12));

    if (keylen == 16) {
        // Use the same key for the other half of the state
        state[8] = state[0];
        state[9] = state[1];
        state[10] = state[2];
        state[11] = state[3];
        state[12] = *((uint32_t*)(key));
        state[13] = *((uint32_t*)(key + 4));
        state[14] = *((uint32_t*)(key + 8));
        state[15] = *((uint32_t*)(key + 12));
    } else {
        // Set the other half of the state to a different constant
        state[8] = 0x786574;
        state[9] = 0x206563;
        state[10] = 0x697550;
        state[11] = 0x6e6b2d;
        state[12] = *((uint32_t*)(key + 16));
        state[13] = *((uint32_t*)(key + 20));
        state[14] = *((uint32_t*)(key + 24));
        state[15] = *((uint32_t*)(key + 28));
    }

    // Save the original state for seeking
    std::memcpy(original_state, state, sizeof(state));
    counter = 0;
}

void ChaCha20::SetIV(const unsigned char* iv, int ivlen) {
    if (ivlen != 8) {
        throw std::runtime_error("invalid IV length");
    }

    // Set the nonce
    state[12] = *((uint32_t*)(iv));
    state[13] =((uint32_t)(iv + 4));
// Reset the counter
    ResetCounter();
}

void ChaCha20::Seek(uint64_t pos) {
// Restore the original state
    std::memcpy(state, original_state, sizeof(state));
    // Set the counter to the desired position
    counter = pos / 64;
    buffer_pos = pos % 64;

    // Generate the initial block
    ChaChaBlock(state);
}

void ChaCha20::Output(const unsigned char* input, unsigned char* output, size_t len) {
    uint32_t i, j;
    for (i = 0; i < len; i++) {
        if (buffer_pos == 64) {
            // Generate the next block
            ChaChaBlock(state);
            buffer_pos = 0;
        }

        output[i] = input[i] ^ buffer[buffer_pos];
        buffer_pos++;
    }
}

void ChaCha20::QuarterRound(uint32_t& a, uint32_t& b, uint32_t& c, uint32_t& d) {
    a += b; d ^= a; d = (d << 16) | (d >> 16);
    c += d; b ^= c; b = (b << 12) | (b >> 20);
    a += b; d ^= a; d = (d << 8) | (d >> 24);
    c += d; b ^= c; b = (b << 7) | (b >> 25);
}

void ChaCha20::ChaChaBlock(uint32_t output[16]) {
    uint32_t i, j;
    // Copy the state to the working buffer
    std::memcpy(buffer, state, sizeof(state));

    // Do 20 rounds of quarter rounds
    for (i = 0; i < rounds; i++) {
        QuarterRound(buffer[0], buffer[4], buffer[8], buffer[12]);
        QuarterRound(buffer[1], buffer[5], buffer[9], buffer[13]);
        QuarterRound(buffer[2], buffer[6], buffer[10], buffer[14]);
        QuarterRound(buffer[3], buffer[7], buffer[11], buffer[15]);
        QuarterRound(buffer[0], buffer[5], buffer[10], buffer[15]);
        QuarterRound(buffer[1], buffer[6], buffer[11], buffer[12]);
        QuarterRound(buffer[2], buffer[7], buffer[8], buffer[13]);
        QuarterRound(buffer[3], buffer[4], buffer[9], buffer[14]);
    }

    // Add the working buffer to the original state
    for (i = 0; i < 16; i++) {
        output[i] = state[i] + buffer[i];
    }

    // Increment the counter
    counter++;
    state[12] += counter;
    if (state[12] == 0) {
        counter++;
        state[13] += counter;
    }
    buffer_pos = 0;
}

void ChaCha20::ResetCounter() {
    state[12] = 0;
    state[13] = 0;
    counter = 0;
    buffer_pos = 0;
}

int main() {
// Example usage
    ChaCha20 chacha;
    unsigned char key[32] ={ 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
    0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc };
    unsigned char iv[8] ={ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };
    const char* plaintext = "Hello, world!";
    size_t plaintext_len = std::strlen(plaintext);
    unsigned char ciphertext[plaintext_len];
    unsigned char decrypted_text[plaintext_len];
    // Set the key and IV
    chacha.SetKey(key, sizeof(key));
    chacha.SetIV(iv, sizeof(iv));

    // Encrypt the plaintext
    chacha.Output((const unsigned char*)plaintext, ciphertext, plaintext_len);

    // Seek to the beginning of the stream
    chacha.Seek(0);

    // Decrypt the ciphertext
    chacha.Output(ciphertext, decrypted_text, plaintext_len);

    // Print the results
    std::cout << "Plaintext: " << plaintext << std::endl;
    std::cout << "Ciphertext: ";
    for (int i = 0; i < plaintext_len; i++) {
        std::cout << std::hex << (int)ciphertext[i];
    }
    std::cout << std::endl;
    std::cout << "Decrypted text: " << decrypted_text << std::endl;

    return 0;
}