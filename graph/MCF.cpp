template<class T>
class MCF {
    using TP = pair<T, int>;
    
    struct edge {
        int to, cap;
        T cost;
        int rev;
        
        edge(int to, int cap, T cost, int rev) : to(to), cap(cap), cost(cost), rev(rev) {}
    };
    
    int n;
    vector <vector<edge>> G;
    vector <T> pot, dist;
    vi prevv, preve;

public:
    explicit MCF(int n) : n(n), G(n), pot(n), dist(n), prevv(n), preve(n) {}
    
    void add_edge(int from, int to, int cap, T cost) {
        G[from].eb(to, cap, cost, G[to].size());
        G[to].eb(from, 0, -cost, G[from].size() - 1);
    }
    
    // return -1 if impossible
    // this must not be called more than once
    // O(F|E|log|V|)
    T min_cost_flow(int s, int t, int f) {
        T res = 0;
        pot.assign(n, 0);
        while (f > 0) {
            // use dijkstra to update pot
            priority_queue <TP, vector<TP>, greater<TP>> q;
            dist.assign(n, numeric_limits<T>::max());
            dist[s] = 0;
            q.emplace(0, s);
            while (!q.empty()) {
                auto[d, u] = q.top();
                q.pop();
                if (dist[u] < d) continue;
                rep(i, G[u].size())
                {
                    const edge &e = G[u][i];
                    if (e.cap > 0 and chmin(dist[e.to], d + e.cost + pot[u] - pot[e.to])) {
                        prevv[e.to] = u;
                        preve[e.to] = i;
                        q.emplace(dist[e.to], e.to);
                    }
                }
            }
            if (dist[t] == numeric_limits<T>::max()) return -1;
            rep(i, n)
            pot[i] += dist[i];
            
            int d = f;
            for (int v = t; v != s; v = prevv[v]) {
                chmin(d, G[prevv[v]][preve[v]].cap);
            }
            f -= d;
            res += pot[t] * d;
            for (int v = t; v != s; v = prevv[v]) {
                edge &e = G[prevv[v]][preve[v]];
                e.cap -= d;
                G[v][e.rev].cap += d;
            }
        }
        return res;
    };
};