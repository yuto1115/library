constexpr int mod = 1000000007;

// constexpr int mod = 998244353;
struct mint {
    ll x;
    
    mint(ll x = 0) : x((x % mod + mod) % mod) {}
    
    mint operator-() const { return mint(-x); }
    
    mint &operator+=(const mint &a) {
        if ((x += a.x) >= mod) x -= mod;
        return *this;
    }
    
    mint &operator++() { return *this += mint(1); }
    
    mint &operator-=(const mint &a) {
        if ((x += mod - a.x) >= mod) x -= mod;
        return *this;
    }
    
    mint &operator--() { return *this -= mint(1); }
    
    mint &operator*=(const mint &a) {
        (x *= a.x) %= mod;
        return *this;
    }
    
    mint operator+(const mint &a) const {
        mint res(*this);
        return res += a;
    }
    
    mint operator-(const mint &a) const {
        mint res(*this);
        return res -= a;
    }
    
    mint operator*(const mint &a) const {
        mint res(*this);
        return res *= a;
    }
    
    mint pow(ll t) const {
        mint res = mint(1), a(*this);
        while (t > 0) {
            if (t & 1) res *= a;
            t >>= 1;
            a *= a;
        }
        return res;
    }
    
    // for prime mod
    mint inv() const { return pow(mod - 2); }
    
    mint &operator/=(const mint &a) { return *this *= a.inv(); }
    
    mint operator/(const mint &a) const {
        mint res(*this);
        return res /= a;
    }
};

ostream &operator<<(ostream &os, const mint &a) { return os << a.x; }
