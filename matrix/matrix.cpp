template<typename T>
struct matrix {
    int h,w;
    vector<vector<T>> v;
    constexpr matrix(int h,int w,T t):h(h),w(w),v(vector<vector<T>>(h,vector<T>(w,t))) {}
    constexpr matrix(const vector<vector<T>> &v):v(v),h(v.size()),w(v[0].size()) {}
    constexpr matrix& operator+=(const matrix& a) { rep(i,h) rep(j,w) v[i][j] += a.v[i][j]; return *this; }
    constexpr matrix& operator*=(const int& k) { rep(i,h) rep(j,w) v[i][j] *= k; return *this; }
    constexpr matrix& operator-=(const matrix& a) { *this += a*(-1); return *this; }
    constexpr matrix operator+(const matrix& a) const { return res(*this) += a; }
    constexpr matrix operator*(const int& k) const { return res(*this) *= k; }
    constexpr matrix operator-(const matrix& a) const { return res(*this) -= a; }
    constexpr matrix operator*(const matrix& a) const {
        matrix res(h,a.w,0);
        rep(i,h) rep(j,a.h) rep(k,a.w) res.v[i][k] += v[i][j]*a.v[j][k];
        return res;
    }
    constexpr matrix& operator*=(const matrix& a) { return *this = *this*a; }
    constexpr matrix pow(ll t) const {
        matrix res(h,w,0),a(*this);
        rep(i,h) res.v[i][i] = 1;
        while(t > 0) {
            if(t&1) res *= a;
            t >>= 1;
            a *= a;
        }
        return res;
    }
    
    vector<T> &operator[](int i) {
        assert(i < h);
        return v[i];
    }
};