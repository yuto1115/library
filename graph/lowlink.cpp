class lowlink {
    vvi G;
    vi ord, low;
    
    int dfs(int v, int p, int k) {
        ord[v] = low[v] = k++;
        bool flag = false;
        int cnt = 0;
        for (int u : G[v]) {
            if (ord[u] < 0) {
                cnt++;
                k = dfs(u, v, k);
                chmin(low[v], low[u]);
                flag |= p >= 0 and ord[v] <= low[u];
                if (ord[v] < low[u]) bridge.eb(v, u);
            } else if (u != p) {
                chmin(low[v], ord[u]);
            }
        }
        flag |= p < 0 and cnt > 1;
        if (flag) articulation.pb(v);
        return k;
    }
    
    void init() {
        ord.assign(G.size(), -1);
        low.assign(G.size(), -1);
        int k = 0;
        rep(i, G.size()) {
            if (ord[i] < 0) k = dfs(i, -1, k);
        }
    }

public:
    vi articulation;
    vp bridge;
    
    lowlink(vvi &G) : G(G) { init(); }
};