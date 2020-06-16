class Bipartite_matching {
    int n;
    vvi G;
    vi match;
    vb used;
    bool dfs(int v) {
        used[v] = true;
        for(int u : G[v]) {
            int w = match[u];
            if(w < 0 || !used[w] && dfs(w)) {
                match[v] = u;
                match[u] = v;
                return true;
            }
        }
        return false;
    }

public:
    Bipartite_matching(int n):n(n),G(n),match(n),used(n) {}
    void add_edge(int v,int u) {
        G[v].pb(u);
        G[u].pb(v);
    }
    int max_matching() {
        int res = 0;
        match.assign(n,-1);
        rep(i,n) {
            if(match[i] >= 0) continue;
            used.assign(n,false);
            if(dfs(i)) res++;
        }
        return res;
    }
};
