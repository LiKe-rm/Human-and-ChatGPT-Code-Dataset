#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

class GF2Elem {
public:
    GF2Elem(bool b = false) : value(b) {}

    GF2Elem operator+(const GF2Elem& other) const {
        return GF2Elem(value ^ other.value);
    }

    GF2Elem operator*(const GF2Elem& other) const {
        return GF2Elem(value && other.value);
    }

    bool operator==(const GF2Elem& other) const {
        return value == other.value;
    }

    bool operator!=(const GF2Elem& other) const {
        return value != other.value;
    }

    friend ostream& operator<<(ostream& os, const GF2Elem& elem) {
        os << elem.value;
        return os;
    }

private:
    bool value;
};

class PolyGF2 {
public:
    PolyGF2() {}

    PolyGF2(const vector<GF2Elem>& coef) {
        coef_ = coef;
        normalize();
    }

    PolyGF2 operator+(const PolyGF2& other) const {
        int n = max(degree(), other.degree());
        vector<GF2Elem> coef(n + 1);
        for (int i = 0; i <= n; ++i) {
            coef[i] = get_coef(i) + other.get_coef(i);
        }
        return PolyGF2(coef);
    }

    PolyGF2 operator*(const PolyGF2& other) const {
        int n = degree();
        int m = other.degree();
        vector<GF2Elem> coef(n + m + 1);
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                coef[i + j] = coef[i + j] + get_coef(i) * other.get_coef(j);
            }
        }
        return PolyGF2(coef);
    }

    PolyGF2 operator/(const PolyGF2& other) const {
        PolyGF2 q, r(*this);
        while (r.degree() >= other.degree()) {
            int d = r.degree() - other.degree();
            vector<GF2Elem> coef(d + 1);
            coef[d] = r.get_coef(r.degree()) / other.get_coef(other.degree());
            PolyGF2 t(coef);
            q = q + t;
            r = r - t * other;
        }
        return q;
    }

    PolyGF2 operator%(const PolyGF2& other) const {
        PolyGF2 q, r(*this);
        while (r.degree() >= other.degree()) {
            int d = r.degree() - other.degree();
            vector<GF2Elem> coef(d + 1);
            coef[d] = r.get_coef(r.degree()) / other.get_coef(other.degree());
            PolyGF2 t(coef);
            q = q + t;
            r = r - t * other;
        }
        return r;
    }

    PolyGF2 operator-(const PolyGF2& other) const {
        return *this + other;
    }

    PolyGF2 operator/(const GF2Elem& other) const {
        vector<GF2Elem> coef;
        for (const auto& c : coef_) {
            coef.push_back(c / other);
        }
        return PolyGF2(coef);
    }

    int degree() const {
        return coef_.size() - 1;
    }

    GF2Elem get_coef(int i) const {
        if (i < 0 || i > degree()) {
            return GF2Elem(false);
        } else {
            return coef_[i];
        }
    }

    void set_coef(int i, const GF2Elem& value) {
        if (i >= 0) {
            if (i >= coef_.size()) {
                coef_.resize(i + 1);
            }
            coef_[i] = value;
            normalize();
        }
    }

    void normalize() {
        while (coef_.size() > 0 && coef_.back() == GF2Elem(false)) {
            coef_.pop_back();
        }
    }

    friend ostream& operator<<(ostream& os, const PolyGF2& poly) {
        if (poly.degree() < 0) {
            os << 0;
        } else {
            for (int i = poly.degree(); i >= 0; --i) {
                if (poly.get_coef(i) != GF2Elem(false)) {
                    if (i < poly.degree()) {
                        os << " + ";
                    }
                    if (i == 0 || poly.get_coef(i) != GF2Elem(true)) {
                        os << poly.get_coef(i);
                    }
                    if (i > 0) {
                        os << "x";
                        if (i > 1) {
                            os << "^" << i;
                        }
                    }
                }
            }
        }
        return os;
    }

private:
    vector<GF2Elem> coef_;
};

class GF2mElem {
public:
    GF2mElem() : value(0) {}

    GF2mElem(unsigned int value) : value(value) {}

    GF2mElem operator+(const GF2mElem& other) const {
        return GF2mElem(value ^ other.value);
    }

    GF2mElem operator-(const GF2mElem& other) const {
        return GF2mElem(value ^ other.value);
    }

    GF2mElem operator*(const GF2mElem& other) const {
        unsigned int r = 0;
        unsigned int m = (1 << m_) - 1;
        unsigned int a = value;
        unsigned int b = other.value;
        while (b != 0) {
            if (b & 1) {
                r ^= a;
            }
            a <<= 1;
            if (a & (1 << m_)) {
                a ^= p_;
            }
            b >>= 1;
        }
        return GF2mElem(r);
    }

    GF2mElem operator/(const GF2mElem& other) const {
        return (*this) * other.inv();
    }

    bool operator==(const GF2mElem& other) const {
        return value == other.value;
    }

    bool operator!=(const GF2mElem& other) const {
        return value != other.value;
    }

    bool is_zero() const {
        return value == 0;
    }

    GF2mElem pow(unsigned int k) const {
        GF2mElem r(1);
        GF2mElem a = *this;
        while (k != 0) {
            if (k & 1) {
                r = r * a;
            }
            a = a * a;
            k >>= 1;
        }
        return r;
    }

    GF2mElem inv() const {
        return pow((1 << m_) - 2);
    }

    friend ostream& operator<<(ostream& os, const GF2mElem& elem) {
        bitset<32> bits(elem.value);
        for (int i = m_ - 1; i >= 0; --i) {
            os << bits[i];
        }
        return os;
    }

    unsigned int get_value() const {
        return value;
    }

private:
    unsigned int value;
    static unsigned int p_;
    static int m_;
};

unsigned int GF2mElem::p_ = 0;
int GF2mElem::m_ = 0;

class BCH {
public:
    BCH(const vector<int>& p, int m, int n, int k, int t) : p_(p), m_(m), n_(n), k_(k), t_(t) {
        init();
    }

    ~BCH() {
        delete[] alpha_;
        delete[] log_;
        delete[] poly_;
    }

    vector<GF2Elem> encode(const vector<GF2Elem>& data) const {
        vector<GF2Elem> code(n_);
        for (int i = 0; i < k_; ++i) {
            code[i] = data[i];
        }
        for (int i = k_; i < n_; ++i) {
            GF2mElem r = eval_poly(poly_, alpha_[i - k_]);
            code[i] = r.get_value();
        }
        return code;
    }

    vector<GF2Elem> decode(const vector<GF2Elem>& received) const {
        vector<GF2mElem> syndrome(t_ * 2);
        for (int i = 0; i < t_ * 2; ++i) {
            GF2mElem s(0);
            for (int j = 0; j < n_; ++j) {
                GF2mElem a = alpha_[i * j % (n_ - 1)];
                s = s + GF2mElem(received[j]).pow(i) * a;
            }
            syndrome[i] = s;
        }
        vector<int> error_pos;
        for (int i = 0; i < syndrome.size(); ++i) {
            if (syndrome[i].is_zero()) {
                error_pos.push_back(i);
            }
        }
        if (error_pos.empty()) {
            return received;
        } else {
            vector<GF2Elem> corrected = received;
            for (int i = 0; i < error_pos.size(); ++i) {
                GF2mElem error_locator(1);
                int error_pos_i = error_pos[i];
                for (int j = 0; j < error_pos.size(); ++j) {
                    if (j != i) {
                        int pos = error_pos[j];
                        error_locator = error_locator * (GF2mElem(alpha_[error_pos_i]) - GF2mElem(alpha_[pos]));
                    }
                }
                GF2mElem error_eval(0);
                for (int j = 0; j < n_; ++j) {
                    error_eval = error_eval + GF2mElem(corrected[j]).pow(error_pos_i) * alpha_[j];
                }
                GF2Elem error_value = GF2Elem(error_eval / error_locator);
                corrected[error_pos_i] = error_value;
            }
            return corrected;
        }
    }

private:
    vector<int> p_;
    int m_;
    int n_;
    int k_;
    int t_;
    GF2mElem* alpha_;
    int* log_;
    PolyGF2 poly_;

    void init() {
        p_.push_back(1);
        for (int i = 0; i < m_; ++i) {
                        p_.push_back(0);
        }
        alpha_ = new GF2mElem[n_];
        log_ = new int[(1 << m_) - 1];
        for (int i = 0; i < n_; ++i) {
            alpha_[i] = GF2mElem(1 << i);
        }
        for (int i = 0; i < (1 << m_) - 1; ++i) {
            log_[i] = -1;
        }
        for (int i = 0; i < n_; ++i) {
            log_[alpha_[i].get_value()] = i;
        }
        vector<GF2Elem> coef(n_ - k_ + 1);
        for (int i = 0; i < n_ - k_ + 1; ++i) {
            coef[i] = GF2Elem(false);
        }
        for (int i = 0; i < k_; ++i) {
            PolyGF2 term(vector<GF2Elem>{GF2Elem(true), GF2Elem(alpha_[i].get_value())});
            coef[n_ - k_ - i] = coef[n_ - k_ - i] + GF2Elem(true);
            poly_ = poly_ + term;
        }
        for (int i = 1; i <= t_; ++i) {
            PolyGF2 q(1);
            for (int j = 1; j <= 2 * i - 1; ++j) {
                q = q * PolyGF2(vector<GF2Elem>{GF2Elem(true), GF2Elem(alpha_[n_ - k_ + j].get_value())});
            }
            PolyGF2 r = (q % poly_) * GF2Elem(alpha_[n_ - k_ + i].get_value()).pow(2 * i - 2);
            poly_ = poly_ + r;
        }
    }

    GF2mElem eval_poly(const PolyGF2& poly, const GF2mElem& x) const {
        GF2mElem r(0);
        for (int i = poly.degree(); i >= 0; --i) {
            r = r * x + GF2mElem(poly.get_coef(i).get_value());
        }
        return r;
    }
};

