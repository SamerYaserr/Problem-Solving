struct DSU {
    vector<int> parent, count;
    int cc;
 
    DSU (int n) {
        count.assign(n + 1, 1), parent.assign(n + 1, 0);
        cc = n;
        for (int i = 1; i <= n; ++i) parent[i] = i;
    }
 
    int root(int u) {
        while (u != parent[u])
            u = parent[u] = parent[parent[u]];
        return u;
    }
 
    void merge(int u, int v) {
        int uRoot = root(u), vRoot = root(v);
        if (uRoot == vRoot) return;
        cc--;
        if (count[uRoot] < count[vRoot]) swap(uRoot, vRoot);
        count[uRoot] += count[vRoot];
        parent[vRoot] = uRoot;
    }
 
    bool sameSet(int u, int v) {
        return root(u) == root(v);
    }
};