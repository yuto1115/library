template<class T, T (*merge)(T, T), T (*add_root)(T, int, int), T (*id)()>
class rerooting {
    int n;
    vvi tree;
    vector <vector<T>> dp;
    vector <T> ans;
    
    T dfs(int u = 0, int p = -1) {
        T sum = id();
        dp[u].resize(tree[u].size());
        rep(i, tree[u].size())
        {
            int v = tree[u][i];
            if (v == p) continue;
            dp[u][i] = dfs(v, u);
            sum = merge(sum, add_root(dp[u][i], u, v));
        }
        return sum;
    }
    
    void dfs2(T dpP, int u = 0, int p = -1) {
        int sz = tree[u].size();
        rep(i, sz)
        if (tree[u][i] == p) dp[u][i] = dpP;
        vector <T> sumL(sz + 1, id()), sumR(sz + 1, id());
        rep(i, sz)
        sumL[i + 1] = merge(sumL[i], add_root(dp[u][i], u, tree[u][i]));
        rrep(i, sz)
        sumR[i] = merge(sumR[i + 1], add_root(dp[u][i], u, tree[u][i]));
        ans[u] = sumL[sz];
        rep(i, sz)
        {
            int v = tree[u][i];
            if (v == p) continue;
            T t = merge(sumL[i], sumR[i + 1]);
            dfs2(t, v, u);
        }
    }

public:
    explicit rerooting(const vvi &tree) : n(tree.size()), tree(tree), dp(n), ans(n) {
        dfs();
        dfs2(id());
    };
    
    T get_ans(int i) {
        return ans[i];
    }
};