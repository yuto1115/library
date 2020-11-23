class polynomial {
    int n;
    vector<T> v;
    
    void shrink() {
        while (n > 0 and v.back() == T(0)) {
            v.pop_back();
            n--;
        }
    }

public:
    polynomial(vector<T> &init) : n(init.size()), v(init) {
        shrink();
    }
    
    polynomial(vector<T> &&init) : n(init.size()), v(init) {
        shrink();
    }
    
    T eval(T x) {
        T res = 0;
        T now = 1;
        rep(i, n) {
            res += v[i] * now;
            now *= x;
        }
        return res;
    }
    
    // P *= (ax + b)
    void multiply(T a = 0, T b = 1) {
        if (n == 0) return;
        v.pb(0);
        rrep(i, n) {
            v[i + 1] += v[i] * a;
            v[i] *= b;
        }
        n++;
        shrink();
    }
    
    void scalar(T k = 1) {
        rep(i, n) v[i] *= k;
        shrink();
    }
    
    // P /= (ax + b)
    void divide(T a = 0, T b = 1) {
        assert(n >= 2);
        assert(a != 0 or b != 0);
        rep(i, n - 1) {
            v[i] /= b;
            v[i + 1] -= v[i] * a;
        }
        assert(v.back() == T(0));
        shrink();
    }
    
    // return f'(x)
    polynomial differ() {
        vector<T> res;
        rep2(i, 1, n) {
            res.pb(v[i] * i);
        }
        return polynomial<T>(res);
    }
    
    // return ∫ f(x)dx
    polynomial integral() {
        if (n == 0) return polynomial<T>(vector<T>());
        vector<T> res = {0};
        rep(i, n) {
            res.pb(v[i] / (i + 1));
        }
        return polynomial<T>(res);
    };
    
    template<typename F>
    friend ostream &operator<<(ostream &, const polynomial<F> &);
};

template<typename T>
ostream &operator<<(ostream &os, const polynomial<T> &f) {
    rrep(i, f.n) {
        os << f.v[i];
        if (i > 0) {
            if(i > 1) os << "x^" << i;
            else os << "x";
            os << " + ";
        }
    }
    return os;
}
