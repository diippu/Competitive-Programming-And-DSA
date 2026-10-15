#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define F first
#define S second
#define int long long
using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using pii = array<int, 2>;
using tup = array<int, 3>;
template <typename T>
using order_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

//linearity of expectation,
//contribution technique

const int N = 1e5 + 5;
vector<int> adj[N], d(N);

void dfs(int u, int p) {
    d[u] = d[p] + 1;
    for (auto v : adj[u]) if(v != p) dfs(v, u);
}

void solve(int tc) {
    int n; cin >> n;
    for (int i = 0; i + 1 < n; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);

    long double ans = 0;
    for (int i = 1; i <= n; ++i) {
        long double a = 1, b = d[i];
        ans += a / b;
    }
    cout << fixed << setprecision(20) << ans << '\n';
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t = 1, tc = 0; //cin >> t;
    while (t--) solve(++tc);
}
