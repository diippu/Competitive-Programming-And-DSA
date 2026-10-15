#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define F first
#define S second
#define int long long
using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using pii = array<int, 2>;
using tup = array<int, 4>;
using LL = __int128;
template <typename T>
using order_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T> using minheap = priority_queue<T, vector<T>, greater<T>>;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
// find_by_order() -> iterator to the k-th largest element (zero based)
// order_of_key() -> the number of items that are strictly smaller
// __builtin_popcount() -> number of ones
// __builtin_clz() -> number of leading 0bits from msb
// __builtin_ctz() -> number of leading 0bits from lsb

const int N = 1e6 + 5;
const int M = 1e9 + 7; //1000000007
const int inf = (ll) 1e18;
vector<int> fac(N), invf(N);


int binpow(int a, int b) {
    int res = 1;
    a %= M;
    while(b > 0) {
        if(b & 1) res = res * a % M;
        a = a * a % M;
        b >>= 1;
    }
    return res;
}

void precal() {
    fac[0] = 1;
    for (int i = 1; i < N; ++i) {
        fac[i] = fac[i - 1] * i % M;
    }

    invf[N - 1] = binpow(fac[N - 1], M - 2);
    for (int i = N - 2; i >= 0; --i) {
        invf[i] = invf[i + 1] * (i + 1) % M;
    }
}

int ncr(int n, int r) {
    if(r > n || n < 0 || r < 0) return 0;

    int res = fac[n] * invf[r] % M;
    return res * invf[n - r] % M;
}

vector<int> l(N), dp(N), adj[N];

void dfs(int u, int p) {
    l[u] = l[p] + 1;
    for (auto v : adj[u]) if(v != p) {
        dfs(v, u);
    }
}

void dfs1(int u, int p) {
    dp[u] = binpow(l[u], M - 2);
    for (auto v : adj[u]) if(v != p) {
        dfs1(v, u);
        dp[u] += dp[v];
        dp[u] %= M;
    }

}

void solve(int tc) {
    int n, m; cin >> n >> m;

    int ans = 0;
    vector<int> a(n + 5);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);

    for (int i = 1; i <= n; ++i) {
        ans += (a[i] * binpow(l[i], M - 2)) % M;//initial answer
        ans %= M;
       // cout << i << " " << ans << '\n';
    }

    dfs1(1, 0);
    //for (int i = 1; i )

    for (int i = 1; i <= m; ++i) {
        int u, x; cin >> u >> x;
        ans += (dp[u] * x) % M;
        ans %= M;
        cout << ans << '\n';
    }

    for (int i = 1; i <= n; ++i) {
        adj[i].clear();
        l[i] = dp[i] = 0;
    }

    //https://toph.co/p/goku-s-tree
}
 
int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    //precal();
    int t = 1; cin >> t;
    for (int tc = 1; tc <= t; ++tc) {
        cout << "Case " << tc << ":\n"; 
        solve(tc);
    }
}
