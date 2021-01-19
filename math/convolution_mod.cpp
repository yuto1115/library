// Number Theoretic Transform
void ntt(vector<mint> &v, bool inverse = false) {
    int n = v.size();
    int h = __builtin_ctz(n);
    assert(1 << h == n);
    rep(i, n) {
        int j = 0;
        rep(k, h) j |= (i >> k & 1) << (h - 1 - k);
        if (i < j) swap(v[i], v[j]);
    }
    // b * 2 -> size of block
    for (int b = 1; b < n; b *= 2) {
        rep(j, b) {
            mint m = mint(3).pow((mod - 1) / (2 * b) * j);
            if (inverse) m = m.inv();
            for (int k = 0; k < n; k += b * 2) {
                mint s = v[j + k];
                mint t = v[j + k + b] * m;
                v[j + k] = s + t;
                v[j + k + b] = s - t;
            }
        }
    }
    if (inverse) rep(i, n) v[i] /= n;
}

// sum_{i + j = k} {a_i * b_j} = c_k
vector<mint> convolution(const vector<mint> &a, const vector<mint> &b) {
    assert(mod == 998244353);
    int s = a.size() + b.size() - 1;
    int t = 1;
    while (t < s) t *= 2;
    vector<mint> A(t), B(t);
    rep(i, a.size()) A[i] = a[i];
    rep(i, b.size()) B[i] = b[i];
    ntt(A);
    ntt(B);
    rep(i, t) A[i] *= B[i];
    ntt(A, true);
    A.resize(s);
    return A;
}