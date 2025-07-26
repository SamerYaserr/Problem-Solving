// B -> number of bits
const int B = 20, M = 1 << B;

// subset contribute to its superset
void solveSub(vector<int>& dp) {
    for (int i = 0; i < B; ++i)
        for (int m = 0; m < M; ++m)
            if ( m & (1 << i) )
                dp[m] += dp[m ^ (1 << i)];
}

// superset contribute to its subset
void solveSup(vector<int>& dp) {
    for (int i = 0; i < B; ++i)
        for (int m = M - 1; ~m; --m)
            if ( m & (1 << i) )
                dp[m ^ (1 << i)] += dp[m];
}
