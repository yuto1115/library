struct edge {
  int to;
  ll len;
  edge(int to, ll l) : to(to), len(l) {}
};

vl dijkstra(int start, const vector<vector<edge>>& v) {
  int n = v.size();
  vl dist(n, linf);
  priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>>
      q;
  q.emplace(0LL, start);
  dist[start] = 0;
  while (!q.empty()) {
    auto p = q.top();
    q.pop();
    if (dist[p.second] < p.first) continue;
    for (auto e : v[p.second]) {
      if (chmin(dist[e.to], p.first + e.len)) {
        q.emplace(p.first + e.len, e.to);
      }
    }
  }
  return dist;
}
