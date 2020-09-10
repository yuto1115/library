class lca {
    int n;
    vvi G;
    int root;
    vi depth;
    vvi par;
    void dfs(int v,int p,int d) {
        par[0][v] = p;
        depth[v] = d;
        for(int u : G[v]) if(u != p) dfs(u,v,d+1);
    }
    void init() {
        n = G.size();
        depth.resize(n);
        par.resize(30);
        rep(i,30) par[i].resize(n);
        dfs(root,-1,0);
        rep(k,29) rep(v,n) {
            if(par[k][v] < 0) par[k+1][v] = -1;
            else par[k+1][v] = par[k][par[k][v]];
        }
    }

public:
    lca(vvi G, int root = 0): G(G), root(root) { init(); }
    int operator()(int u,int v) {
        if(depth[u] > depth[v]) swap(u,v);
        rep(k,30) if((depth[v]-depth[u])>>k&1) v = par[k][v];
        if(u == v) return u;
        rrep(k,30) {
            if(par[k][u] != par[k][v]) {
                u = par[k][u];
                v = par[k][v];
            }
        }
        return par[0][u];
    }
    int dist(int u,int v) {
        int w = this->operator()(u,v);
        return depth[u]+depth[v]-depth[w]*2;
    }
};