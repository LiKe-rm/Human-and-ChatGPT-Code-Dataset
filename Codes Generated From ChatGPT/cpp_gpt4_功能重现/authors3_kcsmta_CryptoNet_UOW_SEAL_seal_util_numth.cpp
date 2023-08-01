#include <iostream>
#include <map>
#include <cmath>
#include <algorithm>

// Function to compute the modular exponentiation (a^b) % m
long long mod_pow(long long a, long long b, long long m) {
    long long result = 1;
    a %= m;

    while (b > 0) {
        if (b & 1) {
            result = (result * a) % m;
        }
        a = (a * a) % m;
        b >>= 1;
    }

    return result;
}

// Function to compute the modular inverse of a modulo m
long long mod_inverse(long long a, long long m) {
    return mod_pow(a, m - 2, m);
}

// Function to implement the Baby-step Giant-step algorithm
long long baby_step_giant_step(long long g, long long b, long long p) {
    long long n = static_cast<long long>(sqrt(p - 1)) + 1;

    // Precompute the first n powers of g modulo p
    std::map<long long, long long> powers;
    for (long long i = 0; i < n; ++i) {
        powers[mod_pow(g, i, p)] = i;
    }

    // Compute g^(-n) modulo p
    long long g_inv_n = mod_inverse(mod_pow(g, n, p), p);

    // Giant steps
    for (long long j = 0; j < n; ++j) {
        long long value = (b * mod_pow(g_inv_n, j, p)) % p;

        // Baby steps
        if (powers.count(value)) {
            return j * n + powers[value];
        }
    }

    return -1;
}

int main() {
    long long g, b, p;
    std::cout << "Enter the values for g, b, and p: ";
    std::cin >> g >> b >> p;

    long long x = baby_step_giant_step(g, b, p);
    if (x == -1) {
        std::cout << "No solution found.\n";
    } else {
        std::cout << "Discrete logarithm (x) is: " << x << "\n";
    }

    return 0;
}
