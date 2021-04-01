template<typename T>
class matrix {
    int h, w;
    vector <vector<T>> v;
public:
    constexpr matrix(const vector <vector<T>> &v) : v(v), h(v.size()), w(v[0].size()) {}
    
    constexpr matrix(int h, int w) : matrix(vector < vector < T >> (h, vector<T>(w))) {}
    
    constexpr int get_h() const { return h; }
    
    constexpr int get_w() const { return w; }
    
    constexpr matrix &operator+=(const matrix &a) {
        rep(i, h)
        rep(j, w)
        v[i][j] += a[i][j];
        return *this;
    }
    
    constexpr matrix &operator*=(const int &k) {
        rep(i, h)
        rep(j, w)
        v[i][j] *= k;
        return *this;
    }
    
    constexpr matrix &operator-=(const matrix &a) {
        *this += a * (-1);
        return *this;
    }
    
    constexpr matrix operator+(const matrix &a) const { return res(*this) += a; }
    
    constexpr matrix operator*(const int &k) const { return res(*this) *= k; }
    
    constexpr matrix operator-(const matrix &a) const { return res(*this) -= a; }
    
    constexpr matrix operator*(const matrix &a) const {
        assert(w == a.get_h());
        matrix res(h, a.get_w());
        rep(i, h)
        rep(j, a.get_h())
        rep(k, a.get_w())
        res[i][k] += v[i][j] * a[j][k];
        return res;
    }
    
    constexpr matrix &operator*=(const matrix &a) { return *this = *this * a; }
    
    constexpr matrix pow(ll t) const {
        matrix res(h, w), a(*this);
        rep(i, h)
        res[i][i] = 1;
        while (t > 0) {
            if (t & 1) res *= a;
            t >>= 1;
            a *= a;
        }
        return res;
    }
    
    constexpr vector <T> &operator[](int i) {
        assert(i < h);
        return v[i];
    }
};