#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define F first
#define S second
using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using lll = __int128;
using pii = array<ll, 2>;
using tup = array<ll, 3>;
template <typename T>
using order_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
 
const int N = 1e5 + 5;
vector<pii> adj[N];
ll inf = 1e18, dis[N][11];
int vis[N];
 
void dijkstra(int s, int k) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, s});
    while(!pq.empty()) {
        ll d = pq.top()[0], u = pq.top()[1];
        pq.pop();
 
        vis[u]++;
        if(vis[u] > k) continue;
      
        for (auto [w, v] : adj[u]) {
            for (int i = 1; i <= k; ++i) {
                if(dis[v][i] >= d + w) {
                    for (int j = k; j > i; --j) {
                        dis[v][j] = dis[v][j - 1];
                    }
                    dis[v][i] = d + w;
                    pq.push({dis[v][i], v});
                    break;
                }
            }
        }
    }
}
 
void solve(int tc) {
    int n, m, k; cin >> n >> m >> k;
    for (int i = 1; i <= m; ++i) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({w, v});
    }
 
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= k; ++j) {
            dis[i][j] = inf;
        }
    }
    dijkstra(1, k);
    for (int i = 1; i <= k; ++i) {
        cout << dis[n][i] << " \n"[i == k];
    }   
    //https://cses.fi/problemset/task/1196/
    //https://www.youtube.com/watch?v=V6H1qAeB-l4
    //https://youkn0wwho.academy/topic-list/dijkstras_algorithm
    //https://cp-algorithms.com/graph/dijkstra.html
}
 
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int t = 1, tc = 0; //cin >> t;
    while(t--) solve(++tc);
}
