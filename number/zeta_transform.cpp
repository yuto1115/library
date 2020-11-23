vi zeta_transform(int n, vi &v) {
    assert(v.size() == 1 << n);
    vi res = v;
    rep(j, n) {
        rep(i, 1 << n) {
            if (i >> j & 1) res[i] += res[i & ~(1 << j)];
        }
    }
    return res;
}
