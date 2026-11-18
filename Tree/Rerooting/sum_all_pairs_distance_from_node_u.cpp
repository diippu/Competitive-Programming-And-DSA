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
 
const int N = 2e5 + 10;
const int M = 1e9 + 7;
 
vector<int> adj[N];
vector<ll> subsiz(N);
vector<ll> outsiz(N);
vector<ll> subdis(N);//all pairs dis sum from node u to the v (within the subtree)
vector<ll> outdis(N);//all pairs dis sum from node u to the v (outside the subtree)
vector<ll> ans(N);//total all pairs dis sum u to v
 
void init() {}
void clearr(int n) {
    for (int i = 1; i <= n; ++i) {
        adj[i].clear();
        subdis[i] = outdis[i] = ans[i] = 0;
    }
}
 
void dfs(int u, int p) {
    subsiz[u] = 1;
    for (auto v : adj[u]) if(v != p) {
        dfs(v, u);
        subsiz[u] += subsiz[v];
        subdis[u] += subsiz[v] + subdis[v]; 
    }
}
 
void dfs1(int u, int p) {
    ans[u] = subdis[u] + outsiz[p] + outdis[p];
    //cout << u << " " << p << " " << otsz << " " << otds << '\n';

    for (auto v : adj[u]) if(v != p) {
        outdis[u] = outdis[p] + outsiz[p] + subdis[u] - subsiz[v] - subdis[v];
        outsiz[u] = outsiz[p] + subsiz[u] - subsiz[v];
        dfs1(v, u);
    }
}
 
void solve(int tc) {
    int n; cin >> n;
    for (int i = 0; i + 1 < n; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
 
    dfs(1, 0);
 

    dfs1(1, 0);

    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << " \n"[i == n];
    }

 
    clearr(n);

    //https://cses.fi/problemset/task/1133
       
}
 
int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; 
    //cin >> t;
    for (int tc = 1; tc <= t; ++tc) {
        //cout << "Case " << tc << ": "; 
        solve(tc);
    }
}
