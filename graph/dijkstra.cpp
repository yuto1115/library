// (to, len)
using vve = vector <vector<pair < int, ll>>>;

vl dijkstra(const vve &G, int start) {
    int n = G.size();
    vl dist(n, linf);
    priority_queue < pair < ll, int >, vector < pair < ll, int >>, greater < pair < ll, int>>> q;
    q.emplace(0LL, start);
    dist[start] = 0;
    while (!q.empty()) {
        auto[d, u] = q.top();
        q.pop();
        if (dist[u] < d) continue;
        for (auto[v, len] : G[u]) {
            if (chmin(dist[v], d + len)) {
                q.emplace(d + len, v);
            }
        }
    }
    return dist;
}