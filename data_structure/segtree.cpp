template<class Monoid>
class segtree {
    using S = typename Monoid::S;
    
    int n;
    vector <S> val;

public:
    constexpr segtree(const vector <S> &init = vector<S>()) {
        int _n = init.size();
        n = 1;
        while (n < _n) n *= 2;
        val.assign(n * 2, Monoid::identity);
        rep(i, _n)
        val[i + n] = init[i];
        rrep(i, n)
        val[i] = Monoid::operate(val[i * 2], val[i * 2 + 1]);
    }
    
    constexpr segtree(int _n) : segtree(vector<S>(_n, Monoid::identity)) {}
    
    // segment [l,r)
    S prod(int l, int r) {
        l += n, r += n;
        S prod_l = Monoid::identity;
        S prod_r = Monoid::identity;
        while (l < r) {
            if (l & 1) prod_l = Monoid::operate(prod_l, val[l++]);
            if (r & 1) prod_r = Monoid::operate(val[--r], prod_r);
            l >>= 1, r >>= 1;
        }
        return Monoid::operate(prod_l, prod_r);
    }
    
    template<class F>
    void update(int i, const F &f) {
        i += n;
        val[i] = f(val[i]);
        while (i > 1) {
            i >>= 1;
            val[i] = Monoid::operate(val[i * 2], val[i * 2 + 1]);
        }
    }
    
    S get(int i) {
        assert(i >= 0 and i < n);
        return val[i + n];
    }
};

class M {
public:
    using S = ;
    
    static constexpr S
    identity =;
    
    static constexpr S
    
    operate(const S &l, const S &r) {
        return;
    }
};