class unionfind {
    int n;
    vector<int> par, rank;
public:
    unionfind(int n) : n(n), par(n, -1), rank(n, 0) {}
    
    int root(int x) {
        if (par[x] < 0) return x;
        else return par[x] = root(par[x]);
    }
    
    bool is_root(int x) { return root(x) == x; }
    
    bool same(int x, int y) { return root(x) == root(y); };
    
    bool merge(int x, int y) {
        x = root(x);
        y = root(y);
        if (x == y) return false;
        if (rank[x] < rank[y]) swap(x, y);
        if (rank[x] == rank[y]) rank[x]++;
        par[x] += par[y];
        par[y] = x;
        return true;
    }
    
    int size(int x) { return -par[root(x)]; };
    
    vi roots() {
        vi res;
        rep(i, n)
        if (root(i) == i) res.pb(i);
        return res;
    }
    
    bool connected() {
        return roots().size() == 1;
    }
};