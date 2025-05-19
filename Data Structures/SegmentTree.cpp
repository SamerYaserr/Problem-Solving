struct Node {
    int val;

    Node(): val(0) {
    }

    Node(int v): val(v) {
    }
};

struct SegTree {
    int tree_size;
    vector<Node> segData;
    Node neutral = Node();

    SegTree(int n) {
        tree_size = 1;
        while (tree_size < n) tree_size *= 2;
        segData.assign(tree_size << 1, neutral);
    }

    Node merge(Node &a, Node &b) {
        Node res = Node();

        return res;
    }

    void build(int node, int lx, int rx, vector<int> &a) {
        if (lx + 1 == rx) {
            if (lx < a.size())
                segData[node] = Node(a[lx]);
            return;
        }

        int mid = lx + (rx - lx) / 2;
        int leftNode = 2 * node + 1;
        int rightNode = leftNode + 1;

        build(leftNode, lx, mid, a);
        build(rightNode, mid, rx, a);

        segData[node] = merge(segData[leftNode], segData[rightNode]);
    }

    void build(vector<int> &a) {
        build(0, 0, tree_size, a);
    }

    void set(int idx, int node, int lx, int rx, int val) {
        if (lx + 1 == rx) {
            segData[node] = Node(val);
            return;
        }

        int mid = lx + (rx - lx) / 2;
        int leftNode = 2 * node + 1;
        int rightNode = leftNode + 1;

        if (idx < mid) set(idx, leftNode, lx, mid, val);
        else set(idx, rightNode, mid, rx, val);

        segData[node] = merge(segData[leftNode], segData[rightNode]);
    }

    void set(int idx, int val) {
        set(idx, 0, 0, tree_size, val);
    }

    Node query(int l, int r, int node, int lx, int rx) {
        if (rx <= l || lx >= r)
            return neutral;
        if (lx >= l && rx <= r)
            return segData[node];

        int mid = lx + (rx - lx) / 2;
        int leftNode = 2 * node + 1;
        int rightNode = leftNode + 1;

        Node part1 = query(l, r, leftNode, lx, mid);
        Node part2 = query(l, r, rightNode, mid, rx);

        return merge(part1, part2);
    }

    Node query(int l, int r) {
        return query(l, r + 1, 0, 0, tree_size);
    }
};