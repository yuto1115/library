template<typename T,typename MERGE,typename ADDROOT>
class rerooting {
    int n;
    vvi tree;
    T identity;
    MERGE merge;
    ADDROOT addRoot;
    vector<vector<T>> dp;
    vector<T> ans;

    T dfs(int v = 0,int p = -1) {
        T sum = identity;
        dp[v].resize(tree[v].size());
        rep(i,tree[v].size()) {
            int u = tree[v][i];
            if(u == p) continue;
            dp[v][i] = dfs(u,v);
            sum = merge(sum,dp[v][i]);
        }
        return addRoot(sum);
    }
    void dfs2(T dpP,int v = 0,int p = -1) {
        int sz = tree[v].size();
        rep(i,sz) if(tree[v][i] == p) dp[v][i] = dpP;
        vector<T> sumL(sz+1,identity),sumR(sz+1,identity);
        rep(i,sz) sumL[i+1] = merge(sumL[i],dp[v][i]);
        rrep(i,sz) sumR[i] = merge(sumR[i+1],dp[v][i]);
        ans[v] = addRoot(sumL[sz]);
        rep(i,sz) {
            int u = tree[v][i];
            if(u == p) continue;
            T t = merge(sumL[i],sumR[i+1]);
            dfs2(addRoot(t),u,v);
        }
    }
    void init() {
        dfs();
        dfs2(identity);
    }

public:
    rerooting(int n,vvi tree,T identity,MERGE merge,ADDROOT addRoot)
            :n(n),tree(tree),identity(identity),merge(merge),addRoot(addRoot),dp(n),ans(n) {
        init();
    };
    T get_ans(int i) {
        return ans[i];
    }
};
