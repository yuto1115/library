class NTT {
    int pr;
    
    constexpr ll pow_mod(ll x, ll n, int m) {
        if (m == 1) return 0;
        ll res = 1;
        ll now = x % m;
        while (n > 0) {
            if (n & 1) res = (res * now) % m;
            now = (now * now) % m;
            n >>= 1;
        }
        return res;
    }
    
    constexpr int primitive_root(int mod) {
        if (mod == 2) return 1;
        if (mod == 167772161) return 3;
        if (mod == 469762049) return 3;
        if (mod == 754974721) return 11;
        if (mod == 998244353) return 3;
        int divs[20] = {};
        divs[0] = 2;
        int cnt = 1;
        int x = (mod - 1) / 2;
        while (x % 2 == 0) x /= 2;
        for (int i = 3; (ll) i * i <= x; i += 2) {
            if (x % i == 0) {
                divs[cnt++] = i;
                while (x % i == 0) {
                    x /= i;
                }
            }
        }
        if (x > 1) divs[cnt++] = x;
        for (int g = 2;; g++) {
            bool ok = true;
            for (int i = 0; i < cnt; i++) {
                if (pow_mod(g, (mod - 1) / divs[i], mod) == 1) {
                    ok = false;
                    break;
                }
            }
            if (ok) return g;
        }
    }

public:
    bool first = true;
    mint sum_e[30]; // sum_e[i] = ies[0] * ... * ies[i - 1] * es[i]
    mint sum_ie[30];  // sum_ie[i] = es[0] * ... * es[i - 1] * ies[i]
    
    void init(int mod) {
        first = false;
        pr = primitive_root(mod);
        mint es[30], ies[30];  // es[i]^(2^(2+i)) == 1
        int cnt2 = __builtin_ctz(mint::get_mod() - 1);
        mint e = mint(pr).pow((mint::get_mod() - 1) >> cnt2), ie = e.inv();
        for (int i = cnt2; i >= 2; i--) {
            // e^(2^i) == 1
            es[i - 2] = e;
            ies[i - 2] = ie;
            e *= e;
            ie *= ie;
        }
        mint now = 1;
        for (int i = 0; i <= cnt2 - 2; i++) {
            sum_e[i] = es[i] * now;
            now *= ies[i];
        }
        now = 1;
        for (int i = 0; i <= cnt2 - 2; i++) {
            sum_ie[i] = ies[i] * now;
            now *= es[i];
        }
    }
    
    void operator()(vector <mint> &a, bool inverse = false) {
        int n = a.size();
        int h = __builtin_ctz(n);
        if (inverse) {
            rrep(ph, h + 1, 1)
            {
                int w = 1 << (ph - 1), p = 1 << (h - ph);
                mint now = 1;
                rep(s, w)
                {
                    int offset = s << (h - ph + 1);
                    rep(i, p)
                    {
                        auto l = a[i + offset];
                        auto r = a[i + offset + p];
                        a[i + offset] = l + r;
                        a[i + offset + p] = (l - r) * now;
                    }
                    now *= sum_ie[__builtin_ctz(~(unsigned int) (s))];
                }
            }
        } else {
            rep(ph, 1, h + 1)
            {
                int w = 1 << (ph - 1), p = 1 << (h - ph);
                mint now = 1;
                rep(s, w)
                {
                    int offset = s << (h - ph + 1);
                    rep(i, p)
                    {
                        auto l = a[i + offset];
                        auto r = a[i + offset + p] * now;
                        a[i + offset] = l + r;
                        a[i + offset + p] = l - r;
                    }
                    now *= sum_e[__builtin_ctz(~(unsigned int) (s))];
                }
            }
        }
    }
} ntt;

vm convolution(const vm &a, const vm &b) {
    if (a.empty()) return {};
    if (b.empty()) return {};
    int s = a.size() + b.size() - 1;
    if (min(a.size(), b.size()) <= 50) {
        vm res(s);
        if (a.size() >= b.size()) {
            rep(i, a.size())
            rep(j, b.size())
            res[i + j] += a[i] * b[j];
        } else {
            rep(j, b.size())
            rep(i, a.size())
            res[i + j] += a[i] * b[j];
        }
        return res;
    }
    int t = 1;
    while (t < s) t *= 2;
    vm A(t), B(t);
    rep(i, a.size())
    A[i] = a[i];
    rep(i, b.size())
    B[i] = b[i];
    if (ntt.first) ntt.init(mint::get_mod());
    ntt(A);
    ntt(B);
    rep(i, t)
    A[i] *= B[i];
    ntt(A, true);
    vm res(s);
    mint it = mint(t).inv();
    rep(i, s)
    res[i] = A[i] * it;
    return res;
}

template<class T>
class polynomial : public vector<T> {
public:
    using vector<T>::vector;
    
    constexpr T
    eval(T
    x) const {
        T res = 0;
        T now = 1;
        rep(i, this->size())
        {
            res += (*this)[i] * now;
            now *= x;
        }
        return res;
    }
    
    // return f'(x)
    constexpr polynomial
    
    differ() const {
        vector <T> res;
        rep2(i, 1, this->size())
        res.pb((*this)[i] * i);
        return polynomial(all(res));
    }
    
    // return ∫ f(x)dx
    constexpr polynomial
    
    integral() const {
        int n = this->size();
        if (n == 0) return vector<T>();
        vector <T> res = {0};
        rep(i, n)
        res.pb((*this)[i] / (i + 1));
        return polynomial(all(res));
    };
    
    constexpr polynomial
    
    operator+(const polynomial &a) const {
        vector <T> res(max(this->size(), a.size()));
        rep(i, this->size())
        res[i] += (*this)[i];
        rep(i, a.size())
        res[i] += a[i];
        return polynomial(all(res));
    }
    
    constexpr polynomial
    
    operator-(const polynomial &a) const {
        vector <T> res(max(this->size(), a.size()));
        rep(i, this->size())
        res[i] += (*this)[i];
        rep(i, a.size())
        res[i] -= a[i];
        return polynomial(all(res));
    }
    
    constexpr polynomial
    
    operator*(const polynomial &a) const {
        vector <T> res = convolution(*this, a);
        return polynomial(all(res));
    }
    
    constexpr polynomial
    
    operator*(T k) const {
        polynomial res(*this);
        rep(i, res.size())
        res[i] *= k;
        return res;
    }
    
    constexpr polynomial
    &
    
    operator+=(const polynomial &a) {
        return *this = *this + a;
    }
    
    constexpr polynomial
    &
    
    operator-=(const polynomial &a) {
        return *this = *this - a;
    }
    
    constexpr polynomial
    &
    
    operator*=(const polynomial &a) {
        return *this = *this * a;
    }
    
    // P *= (ax + b)
    constexpr void multiply(T a = 0, T b = 1) {
        int n = this->size();
        this->push_back(T(0));
        rrep(i, n)
        {
            (*this)[i + 1] += (*this)[i] * a;
            (*this)[i] *= b;
        }
    }
    
    // P /= (ax + b)
    constexpr void divide(T a = 0, T b = 1) {
        int n = this->size();
        assert(n >= 2);
        assert(a != 0 or b != 0);
        if (b == T(0)) {
            assert((*this)[0] == T(0));
            T inv = T(1) / a;
            rep(i, n - 1)(*this)[i] = (*this)[i + 1] * inv;
            this->back() = T(0);
        } else {
            T inv = T(1) / b;
            rep(i, n - 1)
            {
                (*this)[i] *= inv;
                (*this)[i + 1] -= (*this)[i] * a;
            }
            assert(this->back() == T(0));
        }
    }
};

using poly = polynomial<>;