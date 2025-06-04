struct SparseTable {
    static const int mxLog = 21;

    vector<array<int, mxLog>> table;
    vector<int> lg;
    int n;

    SparseTable(int sz) {
        n = sz;
        table.resize(n + 1);
        lg.resize(n + 1);
        for (int i = 0; i <= n; ++i) {
            lg[i] = (i > 0 ? __lg(i) : -1);
        }
    }

    int merge(int l, int r) {
        return min(l, r);
    }
    
    void build(const vector<int> &v) {
        for (int i = 0; i < n; ++i) {
            table[i][0] = v[i];
        }
        
        for (int j = 1; j < mxLog; ++j) {
            for (int i = 0; i + (1 << j) - 1 < n; ++i) {
                int left  = table[i][j - 1];
                int right = table[i + (1 << (j - 1))][j - 1];
                table[i][j] = merge(left, right);
            }
        }
    }

    int query(int l, int r) const {
        int len = r - l + 1;
        int j = lg[len];
        int left  = table[l][j];
        int right = table[r - (1 << j) + 1][j];
        return min(left, right);
    }
};