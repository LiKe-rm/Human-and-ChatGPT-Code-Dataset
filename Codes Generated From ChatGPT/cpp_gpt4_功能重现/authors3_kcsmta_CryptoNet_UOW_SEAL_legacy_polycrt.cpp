#include <iostream>
#include <vector>
#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <NTL/ZZ_pX.h>

using namespace std;
using namespace NTL;

class PolyCRTBuilder {
public:
    PolyCRTBuilder(const ZZ_pX &irr_poly, long n) : irr_poly(irr_poly), n(n) {
        find_roots();
    }

    void vector_to_poly(ZZ_pX &result, const vector<ZZ_p> &values) const {
        result.SetLength(n);
        for (long i = 0; i < n; ++i) {
            result[i] = values[i];
        }
    }

    void poly_to_vector(vector<ZZ_p> &result, const ZZ_pX &poly) const {
        result.resize(n);
        for (long i = 0; i < n; ++i) {
            result[i] = coeff(poly, i);
        }
    }

    void inverse_ntt(ZZ_pX &result, const ZZ_pX &poly) const {
        ZZ_pX tmp = poly % irr_poly;
        result.SetLength(n);
        for (long i = 0; i < n; ++i) {
            eval(result[i], tmp, roots[i]);
        }
    }

private:
    ZZ_pX irr_poly;
    long n;
    vector<ZZ_p> roots;

    void find_roots() {
        roots.resize(n);
        ZZ_p r = to_ZZ_p(1);
        ZZ_p one = to_ZZ_p(1);
        long i = 0;
        while (i < n) {
            if (GCD(irr_poly, ZZ_pX(r) - one) == one) {
                roots[i] = r;
                ++i;
            }
            r += 1;
        }
    }
};

int main() {
    // Initialize NTL's ZZ_p context
    ZZ p = GenPrime_ZZ(17);
    ZZ_p::init(p);

    // Define an irreducible polynomial of degree 4
    ZZ_pX irr_poly;
    SetCoeff(irr_poly, 4, 1);
    SetCoeff(irr_poly, 0, 1);

    // Create a PolyCRTBuilder instance
    PolyCRTBuilder builder(irr_poly, 4);

    // Create a vector of ZZ_p values
    vector<ZZ_p> values = {to_ZZ_p(1), to_ZZ_p(2), to_ZZ_p(3), to_ZZ_p(4)};

    // Convert the vector to a polynomial
    ZZ_pX poly;
    builder.vector_to_poly(poly, values);
    cout << "Poly: " << poly << endl;

    // Perform inverse NTT
    ZZ_pX inv_ntt_result;
    builder.inverse_ntt(inv_ntt_result, poly);
    cout << "Inverse NTT: " << inv_ntt_result << endl;

    // Convert the polynomial back to a vector
    vector<ZZ_p> recovered_values;
    builder.poly_to_vector(recovered_values, inv_ntt_result);
    cout << "Recovered values: ";
    for (const auto &v : recovered_values) {
        cout << v << " ";
    }
    cout << endl;

    return 0;
}
