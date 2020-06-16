// Decomposition of Strongly Connected Components
class scc {
    int n;
    vvi G,rG;
    vi ord,bel;
    vb used;
    void init() {
        rG.resize(n);
        rep(i,n) for(int j : G[i]) rG[j].pb(i);
        bel.resize(n);
        used.resize(n);
    }
    void dfs(int v) {
        used[v] = true;
        for(int u : G[v]) if(!used[u]) dfs(u);
        ord.pb(v);
    }
    void rdfs(int v,int k) {
        used[v] = true;
        bel[v] = k;
        for(int u : rG[v]) if(!used[u]) rdfs(u,k);
    }

public:
    // number of components
    int num;
    scc(vvi G):G(G) {
        n = G.size();
        init();
        used.assign(n,false);
        rep(i,n) if(!used[i]) dfs(i);
        used.assign(n, false);
        int k = 0;
        rrep(i,n) if(!used[ord[i]]) rdfs(ord[i],k++);
        num = k;
    }
    // belonging components(topological order)
    int get(int i) { return bel[i]; }
};
