struct node {
    vector<int> v;
};

struct mergeSortTree {
    int n;
    vector<node> tree;

    mergeSortTree(vector<int>& v) {
        n = 1;
        while ( n < (int)v.size() ) n <<= 1;
        tree = vector<node>( n << 1, node() ), build(v);
    }

    node merge(node& left, node& right) {
        node res;
        int l = 0, r = 0;
        while ( l < left.v.size() and r < right.v.size() ) {
            if (left.v[l] <= right.v[r]) res.v.push_back(left.v[l++]);
            else res.v.push_back(right.v[r++]);
        }
        while ( l < left.v.size() ) res.v.push_back(left.v[l++]);
        while ( r < right.v.size() ) res.v.push_back(right.v[r++]);
        return res;
    }

    void build(vector<int>& v, int at, int lx, int rx) {
        if (rx - lx == 1) {
            if ( lx < (int)v.size() )
                tree[at].v.push_back(v[lx]);
            return;
        }
        int mx = lx + (rx - lx) / 2, left = at * 2 + 1, right = left + 1;
        build(v, left, lx, mx);
        build(v, right, mx, rx);
        tree[at] = merge(tree[2 * at + 1], tree[2 * at + 2]);
    }

    void build(vector<int>& v) {
        build(v, 0, 0, n);
    }

    int lessThan(int l, int r, int val, int at, int lx, int rx) {
        if (lx >= r or rx <= l) return 0;
        if (rx <= r and lx >= l)
            return lower_bound(tree[at].v.begin(), tree[at].v.end(), val) - tree[at].v.begin();
        int mx = lx + (rx - lx) / 2, left = at * 2 + 1, right = left + 1;
        return lessThan(l, r, val, left, lx, mx) + lessThan(l, r, val, right, mx, rx);
    }

    int lessThan(int l, int r, int val) {
        return lessThan(l, r, val, 0, 0, n);
    }

    int greaterThan(int l, int r, int val, int at, int lx, int rx) {
        if (lx >= r or rx <= l) return 0;
        if (rx <= r and lx >= l) {
            int up = upper_bound(tree[at].v.begin(), tree[at].v.end(), val) - tree[at].v.begin();
            return (rx - lx) - up;
        }
        int mx = lx + (rx - lx) / 2, left = at * 2 + 1, right = left + 1;
        return greaterThan(l, r, val, left, lx, mx) + greaterThan(l, r, val, right, mx, rx);
    }

    int greaterThan(int l, int r, int val) {
        return greaterThan(l, r, val, 0, 0, n);
    }
};