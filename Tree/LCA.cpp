struct LCA {
    int n, lg;
    vector<vector<int>> adj;
    vector<int> depth;
    vector<vector<int>> up, qu;

    LCA(int sz) {
        n = sz, lg = __lg(sz);
        depth = vector<int>(n + 1);
        adj = vector<vector<int>>(n + 1);
        up = vector<vector<int>>(n + 1, vector<int>(lg + 1) );
        qu = vector<vector<int>>(n + 1, vector<int>(lg + 1) );
    }

    int query(int a, int b) {
        return 0;
    }

    int path(int a, int dist) {
        int ans = 0;
        for (int i = lg; i >= 0; --i) {
            if (dist >= (1 << i)) {
                ans = query(ans, qu[a][i]);
                a = up[a][i];
                dist -= (1 << i);
            }
        }
        return ans;
    }

    void build(int u, int p) {
        up[u][0] = p;
        for (int i = 1; i <= lg; ++i) {
            up[u][i] = up[up[u][i - 1]][i - 1];
            qu[u][i] = query(qu[u][i - 1], qu[up[u][i - 1]][i - 1]);
        }
        for (int v : adj[u]) {
            if (v == up[u][0]) continue;
            depth[v] = depth[u] + 1;
            build(v, u);
        }
    }

    int kthAncestor(int a, int k) {
        if (depth[a] < k) return -1;
        for (int i = lg; i >= 0; --i)
            if ( k >= (1 << i) ) a = up[a][i], k -= (1 << i);
        return a;
    }

    int lca(int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);

        int k = depth[a] - depth[b];
        for (int i = lg; i >= 0; --i)
            if ( k & (1 << i) ) a = up[a][i];

        if (a == b) return a;

        for (int i = lg; i >= 0; --i)
            if (up[a][i] != up[b][i]) a = up[a][i], b = up[b][i];
        return up[a][0];
    }

    int distance(int a, int b) {
        int c = lca(a, b);
        int x = depth[a] - depth[c];
        int y = depth[b] - depth[c];
        return x + y;
    }

    bool isOnPath(int u, int v, int c) {
        int lca1 = lca(u, v);
        int lca2 = lca(u, c);
        int lca3 = lca(v, c);
        return lca1 == c or (lca2 == lca1 and lca3 == c) or (lca3 == lca1 and lca2 == c);
    }

    int calc(int u, int v) {
        int c = lca(u, v);
        int distU = distance(u, c);
        int distV = distance(v, c);

        int ans = path(u, distU) + path(v, distV);
        return ans;
    }

    int kthNode(int u, int v, int k) {
        // k should be  0-indexed
        int c = lca(u, v);
        int distU = distance(u, c);
        int dist = distance(u, v);

        if (k <= distU)
            return kthAncestor(u, k);
        else
            return kthAncestor(v, dist - k);
    }
};