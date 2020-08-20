class sieve {
    int n;
    vi val;
    
    void init() {
        rep(i, n + 1)
        val[i] = i;
        for (int i = 2; i * i <= n; i++) {
            if (val[i] != i) continue;
            for (int j = i * 2; j <= n; j += i) {
                if (val[j] == j) val[j] = i;
            }
        }
    }

public:
    sieve(int n) : n(n), val(n + 1) {
        init();
    }
    
    map<int, int> factorlist(int x) {
        if (n < 2) return {};
        map<int, int> ret;
        int now = x;
        while (now > 1) {
            ret[val[now]]++;
            now /= val[now];
        }
        return ret;
    }
    
    vi unique_factor(int x) {
        map<int, int> m = factorlist(x);
        vi ret;
        for (P p : m) ret.pb(p.first);
        return ret;
    };
    
    bool isPrime(int x) {
        return x >= 2 and val[x] == x;
    }
    
    int count_divisor(int x) {
        int ret = 1;
        map<int, int> fl = factorlist(x);
        for (auto p : fl) ret *= p.second + 1;
        return ret;
    };
}
