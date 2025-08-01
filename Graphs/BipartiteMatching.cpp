struct HopcroftKarp {
    static const int inf = 1'000'000'000;

    // one indexed, O( E * SQRT(V) )
    int n;
    vector<int> l, r, dist;
    vector<vector<int>> adj;

    HopcroftKarp(int _n, int _m) {
        n = _n;
        int total = _n + _m + 1;
        l.assign(total, 0);
        r.assign(total, 0);
        dist.assign(total, 0);
        adj.assign(total, {});
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v + n);
    }

    bool bfs() {
        queue<int> q;
        for (int u = 1; u <= n; u++) {
            if (not l[u]) dist[u] = 0, q.push(u);
            else dist[u] = inf;
        }
        dist[0] = inf;
        while ( not q.empty() ) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (dist[r[v]] == inf) {
                    dist[r[v]] = dist[u] + 1;
                    q.push(r[v]);
                }
            }
        }
        return dist[0] != inf;
    }

    bool dfs(int u) {
        if (not u) return true;
        for (int v : adj[u]) {
            if ( dist[r[v]] == dist[u] + 1 and dfs(r[v]) ) {
                l[u] = v, r[v] = u;
                return true;
            }
        }
        dist[u] = inf;
        return false;
    }

    int maximumMatching() {
        int ans = 0;
        while ( bfs() ) {
            for (int u = 1; u <= n; u++) {
                if ( not l[u] and dfs(u) ) {
                    ++ans;
                }
            }
        }
        return ans;
    }
};