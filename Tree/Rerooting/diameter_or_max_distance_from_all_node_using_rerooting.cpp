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
vector<int> d1(N), d2(N);//first and second max distnc from a node u within subtree
vector<int> out(N);//max distnc from u outside the subtree
vector<int> d(N);//overall max distnc from a node u
 
void init() {}
void clearr(int n) {
    for (int i = 1; i <= n; ++i) {
        adj[i].clear();
        d1[i] = d2[i] = d[i] = out[i] = 0;
    }
}
 
void dfs(int u, int p) {
    for (auto v : adj[u]) if(v != p) {
        dfs(v, u);
        if(1 + d1[v] > d1[u]) {
            d2[u] = d1[u];
            d1[u] = 1 + d1[v];
        } else if(1 + d1[v] > d2[u]) {
            d2[u] = 1 + d1[v];
        }
    }
}
 
void dfs1(int u, int p) {
    d[u] = max(d1[u], 1 + out[p]);
 
    for (auto v : adj[u]) if(v != p) {
        if(1 + d1[v] == d1[u]) {
            out[u] = max(1 + out[p], d2[u]);  
        } else {
            out[u] = max(1 + out[p], d1[u]);
        }
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
 
    out[0] = -1;
    dfs1(1, 0);
    for (int i = 1; i <= n; ++i) {
        cout << d[i] << " \n"[i == n];
    }
 
    clearr(n);
    //https://cses.fi/problemset/task/1132
       
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
