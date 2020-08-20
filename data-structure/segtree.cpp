template<typename T, typename MERGE, typename UPDATE>
class segtree {
    int n;
    vector <T> val;
    T identity;
    MERGE merge;
    UPDATE _update;

public:
    segtree(int _n, vector <T> init, T identity,
            MERGE merge, UPDATE update)
        : identity(identity), merge(merge), _update(update) {
        n = 1;
        while (n < _n) n *= 2;
        val.assign(2 * n - 1, identity);
        rep(i, _n)
        val[i + n - 1] = init[i];
        rrep(i, n - 1)
        val[i] = merge(val[i * 2 + 1], val[i * 2 + 2]);
    }
    
    void update(int i, T x) {
        i += n - 1;
        val[i] = _update(val[i], x);
        while (i > 0) {
            i = (i - 1) / 2;
            val[i] = merge(val[i * 2 + 1], val[i * 2 + 2]);
        }
    }
    
    // segment [a,b)
    T query(int a, int b, int k = 0, int l = 0, int r = -1) {
        if (r == -1) r = n;
        if (b <= l || r <= a) return identity;
        if (a <= l && r <= b) return val[k];
        T t1 = query(a, b, 2 * k + 1, l, (l + r) / 2);
        T t2 = query(a, b, 2 * k + 2, (l + r) / 2, r);
        return merge(t1, t2);
    }
    
    T operator[](int i) const { return val[i]; }
};
