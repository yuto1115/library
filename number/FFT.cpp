// Fast Fourier Transform
namespace FFT {
    using comp = complex<double>;
    
    void dft(vector<comp> &v, int inverse) {
        int sz = v.size();
        if (sz == 1) return;
        vector<comp> a, b;
        rep(i, sz / 2) {
            a.pb(v[2 * i]);
            b.pb(v[2 * i + 1]);
        }
        dft(a, inverse);
        dft(b, inverse);
        double arg = inverse * 2.0 * acos(-1) / sz;
        comp now = 1, zeta = polar(1.0, arg);
        rep(i, sz) {
            v[i] = a[i % (sz / 2)] + now * b[i % (sz / 2)];
            now *= zeta;
        }
    }
    
    vl multiply(vi &f, vi &g) {
        vector<comp> nf, ng;
        int sz = 1;
        while (sz < f.size() + g.size() - 1) sz *= 2;
        nf.resize(sz);
        ng.resize(sz);
        rep(i, f.size()) nf[i] = f[i];
        rep(i, g.size()) ng[i] = g[i];
        dft(nf, 1);
        dft(ng, 1);
        rep(i, sz) nf[i] *= ng[i];
        dft(nf, -1);
        vl res(sz);
        rep(i, sz) res[i] = llround(nf[i].real() / sz);
        return res;
    }
};
