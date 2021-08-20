template<class M>
class lazy_segtree {
    using S = typename M::S;
    using F = typename M::F;
    
    int n, log;
    vector <S> d;
    vector <F> lz;
    
    void update(int k) { d[k] = M::op(d[2 * k], d[2 * k + 1]); }
    
    void all_apply(int k, F f) {
        d[k] = M::mapping(f, d[k]);
        if (k < n) lz[k] = M::composition(f, lz[k]);
    }
    
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = M::id;
    }

public:
    constexpr lazy_segtree() : lazy_segtree(0) {}
    
    constexpr lazy_segtree(int _n) : lazy_segtree(vector<S>(_n, M::e)) {}
    
    constexpr lazy_segtree(const vector <S> &v) {
        log = 0;
        while (1 << log < (int) v.size()) log++;
        n = 1 << log;
        d.assign(2 * n, M::e);
        lz.assign(n, M::id);
        rep(i, v.size())
        d[n + i] = v[i];
        rrep(i, n, 1)
        update(i);
    }
    
    void set(int p, S x) {
        assert(0 <= p and p < n);
        p += n;
        rrep(i, log + 1, 1)
        push(p >> i);
        d[p] = x;
        rep(i, 1, log + 1)
        update(p >> i);
    }
    
    S get(int p) {
        assert(0 <= p and p < n);
        p += n;
        rrep(i, log + 1, 1)
        push(p >> i);
        return d[p];
    }
    
    S prod(int l, int r) {
        assert(0 <= l and l <= r and r <= n);
    
        l += n, r += n;
    
        rrep(i, log + 1, 1)
        {
            if ((l >> i) << i != l) push(l >> i);
            if ((r >> i) << i != r) push(r >> i);
        }
    
        S sl = M::e, sr = M::e;
        while (l < r) {
            if (l & 1) sl = M::op(sl, d[l++]);
            if (r & 1) sr = M::op(d[--r], sr);
            l >>= 1, r >>= 1;
        }
        
        return M::op(sl, sr);
    }
    
    void apply(int l, int r, F f) {
        assert(0 <= l and l <= r and r <= n);
    
        l += n, r += n;
    
        rrep(i, log + 1, 1)
        {
            if ((l >> i) << i != l) push(l >> i);
            if ((r >> i) << i != r) push(r >> i);
        }
    
        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1, r >>= 1;
            }
            l = l2, r = r2;
        }
    
        rep(i, 1, log + 1)
        {
            if ((l >> i) << i != l) update(l >> i);
            if ((r >> i) << i != r) update(r >> i);
        }
    }
};

class M {
public:
    using S = ;
    
    static constexpr S
    e =;
    
    static constexpr S
    
    op(const S &l, const S &r) {
        return;
    }
    
    using F = ;
    
    static constexpr F
    id =;
    
    static constexpr F
    
    composition(const F &g, const F &f) {
        return;
    }
    
    static constexpr S
    
    mapping(const F &f, const S &x) {
        return;
    }
};