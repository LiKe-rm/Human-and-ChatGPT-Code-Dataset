#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>

class BCH_Encoder_Decoder {
public:
    BCH_Encoder_Decoder(const std::vector<int>& irreducible_poly, int m, int n, int k, int t)
        : m(m), n(n), k(k), t(t), alpha_to(1 << m, 0), index_of(1 << m, 0) {
        generate_gf(irreducible_poly);
        generate_gpolynomial();
    }

    ~BCH_Encoder_Decoder() {}

    std::vector<int> encode(const std::vector<int>& data) {
        assert(static_cast<int>(data.size()) == k);
        std::vector<int> codeword(n, 0);

        for (int i = 0; i < k; ++i) {
            codeword[i] = data[i];
        }

        for (int i = 0; i < k; ++i) {
            if (codeword[i]) {
                for (size_t j = 0; j < g.size(); ++j) {
                    codeword[i + j] ^= g[j];
                }
            }
        }

        for (int i = 0; i < k; ++i) {
            codeword[i] = data[i];
        }

        return codeword;
    }

    std::vector<int> decode(std::vector<int>& received) {
        assert(static_cast<int>(received.size()) == n);

        std::vector<int> syndromes(2 * t, 0);

        for (int i = 0; i < n; ++i) {
            if (received[i]) {
                for (int j = 0; j < 2 * t; ++j) {
                    syndromes[j] ^= alpha_to[(i * (j + 1)) % ((1 << m) - 1)];
                }
            }
        }
    std::vector<int> error_locations = find_error_locations(syndromes);
    correct_errors(received, error_locations);

    std::vector<int> decoded_data(k, 0);
    for (int i = 0; i < k; ++i) {
        decoded_data[i] = received[i];
    }

    return decoded_data;
}
private:
    void generate_gf(const std::vector<int>& irreducible_poly) {
    int mask = 1;
    alpha_to[m] = 0;
        for (int i = 0; i < m; ++i) {
            alpha_to[i] = mask;
            index_of[alpha_to[i]] = i;

            if (irreducible_poly[i]) {
                alpha_to[m] ^= mask;
            }

            mask <<= 1;
        }

        index_of[alpha_to[m]] = m;
        mask >>= 1;

        for (int i = m + 1; i < (1 << m) - 1; ++i) {
            alpha_to[i] = alpha_to[i - 1] ^ ((alpha_to[i - 1] & mask) ? alpha_to[m] : 0);
            index_of[alpha_to[i]] = i;
        }

        index_of[0] = -1;
    }

    void generate_gpolynomial() {
        std::vector<int> tmp(2 * t + 1, 0);
        g.resize(t + 1, 0);
        tmp[0] = 1;
        g[0] = 1;

        for (int i = 1; i <= t; ++i) {
            for (int j = i - 1; j > 0; --j) {
                if (tmp[j]) {
                    tmp[j] = alpha_to[(index_of[tmp[j]] + i) % ((1 << m) - 1)];
                }
                tmp[j] ^= tmp[j - 1];
            }
            tmp[i] = 1;

            for (int j = 0; j <= i; ++j) {
                g[i - j] ^= tmp[j];
            }
        }
    }

    std::vector<int> find_error_locations(const std::vector<int>& syndromes) {
        std::vector<int> error_locations;
        // Implement Berlekamp-Massey algorithm or other error-location finding algorithms here.
        // The result should be a vector of error locations.
        return error_locations;
    }

    void correct_errors(std::vector<int>& received, const std::vector<int>& error_locations) {
        for (int loc : error_locations) {
            received[loc] ^= 1;
        }
    }

    int m, n, k, t;
    std::vector<int> alpha_to, index_of, g;
};
