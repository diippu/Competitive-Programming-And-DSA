const int M = 1e9 + 7;
vector<vector<int>> multiply(vector<vector<int>> a, vector<vector<int>> b) {
    int sz = a.size();
    vector<vector<int>> c(sz, vector<int> (sz, 0));
    for (int i = 0; i < sz; i++) 
        for (int j = 0; j < sz; j++) 
            for (int k = 0; k < sz; k++) 
                c[i][j] = (c[i][j] + 1ll * a[i][k] * b[k][j]) % M;
    
    return c;
}
vector<vector<int>> binexpo(vector<vector<int>> m, ll n) {
    vector<vector<int>> res 
    = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
    
    while(n > 0) {
        if(n & 1ll) res = multiply(res, m);
        m = multiply(m, m);
        n >>= 1;
    }
    return res;
}
vector<vector<int>> m 
= {{3, 2, 1, 3}, {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 1}};
vector<vector<int>> b 
= {{3, 0, 0, 0}, {2, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}
}; 
auto res = binexpo(m, k - 2);
res = multiply(res, b);
