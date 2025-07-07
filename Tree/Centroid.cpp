vector<vector<int>> adj;

vector<bool> isCent;
vector<int> subSize;

void preDfs(int v, int p) {
    subSize[v] = 1;
    for (int u : adj[v]) {
        if (u == p or isCent[u]) {
            continue;
        }
        preDfs(u, v);
        subSize[v] += subSize[u];
    }
}

int findCent(int v, int p, int compare) {
    for (int u : adj[v]) {
        if (u != p and not isCent[u] and 2 * subSize[u] > compare) {
            return findCent(u, v, compare);
        }
    }
    return v;
}

void solve(int v) {
    preDfs(v, -1);
    int cent = findCent(v, -1, subSize[v]);
    isCent[cent] = true;
    // update answer
    for (int u : adj[cent]) {
        if (not isCent[u]) {
            solve(u);
        }
    }
}