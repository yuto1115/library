template<class Monoid>
class segtree {
    using T = typename Monoid::value_type;
    
    int n;
    vector<T> val;

public:
    constexpr segtree(int _n) {
        n = 1;
        while (n < _n) n *= 2;
        val = vector<T>(2 * n, Monoid::identity);
    }
    
    constexpr segtree(const vector <T> &init = vector<T>()) {
        int _n = init.size();
        n = 1;
        while (n < _n) n *= 2;
        val = vector<T>(2 * n, Monoid::identity);
        rep(i, _n)
        val[i + n] = init[i];
        rrep(i, n)
        val[i] = Monoid::operate(val[i * 2], val[i * 2 + 1]);
    }
    
    // segment [l,r)
    T fold(int l, int r) {
        l += n, r += n;
        T fold_l = Monoid::identity;
        T fold_r = Monoid::identity;
        while (l < r) {
            if (l & 1) fold_l = Monoid::operate(fold_l, val[l++]);
            if (r & 1) fold_r = Monoid::operate(val[--r], fold_r);
            l >>= 1, r >>= 1;
        }
        return Monoid::operate(fold_l, fold_r);
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
    
    
    T get(int i) {
        assert(i >= 0 and i < n);
        return val[i + n];
    }
};

class Node {
public:
    using value_type = ;
    
    value_type value;
    
    Node(value_type value) : value(value) {}
    
    static constexpr value_type identity = ;
    
    static constexpr value_type operate(const value_type &l, const value_type &r) {
        return ;
    }
};