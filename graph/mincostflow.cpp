template<typename T>
class Mincostflow {
    using TP = pair<T,int>;
    struct edge {
        int to,cap,rev;
        T cost;
        edge(int to,int cap,T cost,int rev):to(to),cap(cap),cost(cost),rev(rev) {}
    };
    T tinf;
    int n;
    vector<vector<edge>> G;
    vector<T> pot,dist;
    vi prevv,preve;
    // potential
    void tinf_init(int x) { tinf = inf; }
    void tinf_init(ll x) { tinf = linf; }

public:
    explicit Mincostflow(int n):n(n),G(n),pot(n),dist(n),prevv(n),preve(n) {
        T x = 0; tinf_init(x);
    }
    void add_edge(int from,int to,T cap,int cost) {
        G[from].eb(to,cap,cost,G[to].size());
        G[to].eb(from,0,-cost,G[from].size()-1);
    }
    // return -1 if impossible
    // this must not be called more than once
    T min_cost_flow(int s,int t,int f) {
        T res = 0;
        pot.assign(n,0);
        while(f > 0) {
            // use dijkstra to update pot
            priority_queue<TP,vector<TP>,greater<TP>> q;
            dist.assign(n,tinf);
            dist[s] = 0;
            q.emplace(0,s);
            while(!q.empty()) {
                T np = q.top().first;
                int v = q.top().second;
                q.pop();
                if(dist[v] < np) continue;
                rep(i,G[v].size()) {
                    edge &e = G[v][i];
                    if(e.cap > 0 && dist[e.to] > dist[v]+e.cost+pot[v]-pot[e.to]) {
                        dist[e.to] = dist[v]+e.cost+pot[v]-pot[e.to];
                        prevv[e.to] = v;
                        preve[e.to] = i;
                        q.emplace(dist[e.to],e.to);
                    }
                }
            }
            if(dist[t] == tinf) return -1;
            rep(i,n) pot[i] += dist[i];

            int d = f;
            for(int v = t; v != s; v = prevv[v]) {
                chmin(d,G[prevv[v]][preve[v]].cap);
            }
            f -= d;
            res += d*pot[t];
            for(int v = t; v != s; v = prevv[v]) {
                edge &e = G[prevv[v]][preve[v]];
                e.cap -= d;
                G[v][e.rev].cap += d;
            }
        }
        return res;
    };
};