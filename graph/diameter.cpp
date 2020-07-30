// G is the tree
// can calc diameter by "dfs(dfs(0).second).first"
P dfs(int v, int p = -1) {
  int ret = 0, ind = v;
  for (int u : G[v]) {
    if (u == p) continue;
    auto d = dfs(u, v);
    if (chmax(ret, d.first + 1)) ind = d.second;
  }
  return {ret, ind};
}
