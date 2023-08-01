#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int power(int x, unsigned int y, int p) {
    int res = 1;
    x = x % p;

    while (y > 0) {
        if (y & 1)
            res = (res * x) % p;

        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;

    if (n % 2 == 0 || n % 3 == 0)
        return false;

    for (int i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;

    return true;
}

int findPrimitiveRoot(int p) {
    if (!isPrime(p)) {
        std::cout << "Error: p must be a prime number." << std::endl;
        return -1;
    }

    std::vector<int> factors;
    int phi = p - 1;

    for (int i = 2; i * i <= phi; ++i) {
        if (phi % i == 0) {
            factors.push_back(i);
            while (phi % i == 0)
                phi /= i;
        }
    }

    for (int r = 2; r <= p; ++r) {
        bool ok = true;
        for (int factor : factors) {
            if (power(r, (p - 1) / factor, p) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return r;
    }

    return -1;
}

int randomPrimitiveRoot(int p) {
    if (!isPrime(p)) {
        std::cout << "Error: p must be a prime number." << std::endl;
        return -1;
    }

    std::srand(std::time(nullptr));
    int r;

    while (true) {
        r = std::rand() % (p - 1) + 1;
        if (gcd(r, p - 1) == 1) break;
    }

    return r;
}

int modInverse(int a, int m) {
    int g = gcd(a, m);
    if (g != 1) {
        std::cout << "Error: inverse doesn't exist" << std::endl;
        return -1;
    }

    return power(a, m - 2, m);
}
