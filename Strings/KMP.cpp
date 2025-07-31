struct KMP {
    int m;
    string pattern;
    vector<int> phi;
    vector< array<int, 26> > transition;

    void build(string& s) {
        pattern = s, m = pattern.size();
        phi.assign(m, 0);
        int ix = 1, match = 0;
        while (ix < m) {
            if (pattern[ix] == pattern[match])
                match++, phi[ix] = match, ix++;
            else if (match != 0)
                match = phi[match - 1];
            else
                phi[ix] = 0, ix++;
        }

        pattern.push_back('#');
        transition.assign( m + 1, array<int, 26>() );
        for (int i = 0; i <= m; i++) {
            for (int c = 0; c < 26; c++) { // offset 'a' can be changed
                if (i < m and 'A' + c == pattern[i]) transition[i][c] = i + 1;
                else if (i == 0) transition[i][c] = 0;
                else transition[i][c] = transition[ phi[i - 1] ][c];
            }
        } pattern.pop_back();
    }

    vector<int> search(string& s) {
        vector<int> ret;
        int ix = 0, jx = 0, n = s.size();
        while ( (n - ix) >= (m - jx) ) {
            if (jx == m)
                ret.push_back(ix - jx), jx = phi[jx - 1];
            while (jx != 0 and pattern[jx] != s[ix])
                jx = phi[jx - 1];
            if (s[ix] == pattern[jx])
                ++ix, ++jx;
            else
                ++ix;
        }
        return ret;
    }
};