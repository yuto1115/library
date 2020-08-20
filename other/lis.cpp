int lis(int n, const vi &v) {
    vi dp(n, inf);
    dp[0] = v[0];
    int now = 0;
    rep2(i, 1, n) {
        if (v[i] > dp[now]) {
            dp[now + 1] = v[i];
            now++;
        } else {
            auto it = upper_bound(all(dp), v[i]);
            *it = v[i];
        }
    }
    return now + 1;
}
