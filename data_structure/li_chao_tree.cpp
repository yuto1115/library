// Convex Hull Trix (Minimum)
class li_chao_tree {
    int n;
    vl xs;
    // y = ax + b
    vl a, b;
    vi ls, rs;
    
    ll eval(ll na, ll nb, int x) {
        return na * xs[x] + nb;
    }
    
    void add(int k, ll na, ll nb) {
        int l = ls[k], r = rs[k], m = (l + r) / 2;
        if (l + 1 == r) {
            if (eval(a[k], b[k], l) > eval(na, nb, l)) {
                a[k] = na;
                b[k] = nb;
            }
            return;
        }
        if (eval(a[k], b[k], l) <= eval(na, nb, l) and eval(a[k], b[k], r) <= eval(na, nb, r)) return;
        if (eval(a[k], b[k], l) >= eval(na, nb, l) and eval(a[k], b[k], r) >= eval(na, nb, r)) {
            a[k] = na;
            b[k] = nb;
            return;
        }
        if (eval(a[k], b[k], m) > eval(na, nb, m)) {
            swap(a[k], na);
            swap(b[k], nb);
        }
        if (eval(a[k], b[k], l) > eval(na, nb, l)) {
            add(2 * k, na, nb);
            return;
        }
        if (eval(a[k], b[k], r) > eval(na, nb, r)) {
            add(2 * k + 1, na, nb);
            return;
        }
    }
    
    void init(const vl &_xs) {
        n = 1;
        while (n < (int) _xs.size()) n *= 2;
        a.assign(2 * n, 0);
        b.assign(2 * n, linf);
        ls.resize(2 * n);
        rs.resize(2 * n);
        rep(i, n)
        {
            ls[n + i] = i;
            rs[n + i] = i + 1;
        }
        rrep(i, n)
        {
            ls[i] = ls[2 * i];
            rs[i] = rs[2 * i + 1];
        }
        xs.resize(n + 1, _xs.back() + 1);
        rep(i, _xs.size())
        xs[i] = _xs[i];
    }

public:
    li_chao_tree(const vl &_xs) {
        assert(is_sorted(all(xs)));
        init(_xs);
    }
    
    li_chao_tree(int n) {
        vl v(n);
        iota(all(v), 0);
        init(v);
    }
    
    ll get_min(int i) {
        assert(0 <= i and i < n);
        int x = i;
        i += n;
        ll res = linf;
        while (i >= 1) {
            chmin(res, eval(a[i], b[i], x));
            i >>= 1;
        }
        return res;
    }
    
    void add_line(ll na, ll nb) {
        add(1, na, nb);
    }
    
    void add_segment(int l, int r, ll na, ll nb) {
        assert(0 <= l and l <= r and r <= n);
        l += n, r += n;
        while (l < r) {
            if (l & 1) add(l++, na, nb);
            if (r & 1) add(--r, na, nb);
            l >>= 1, r >>= 1;
        }
    }
};
