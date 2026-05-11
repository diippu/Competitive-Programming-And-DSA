/*articulation bridge, bridge tree
articulation bridge: if we remove this, it increases the number of components
find components: without taking the bridge the large number of components 
we can take
bridge tree: connect all these components with articulation bridges, it will be a tree
*/
#include<bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using tup = tuple<int, int, int>;

const int N = 3e5 + 5;
vector<int> low(N), tin(N), comp(N), components[N];
vector<int> deg(N);
vector<bool> vis(N), isBridge(N), goldEdge(N), goldNode(N);
vector<pii> adj[N], bridges, edges, bridgeTree[N];
int t, compnum, a, b;
bool flag, paisi;

void clear(int n) {
    for (int i = 0; i <= n; i++) {
        components[i].clear();
        bridgeTree[i].clear();
        adj[i].clear();
        deg[i] = vis[i] = isBridge[i] = 0;
        low[i] = tin[i] = comp[i] = 0;
    }
    bridges.clear();
    edges.clear();
    t = compnum = 0;
}

void dfs(int u, int par) {
    vis[u] = 1;
    tin[u] = low[u] = ++t;
    for (auto [v, edgenum] : adj[u]) {
        if(v == par) continue;
        else if(vis[v]) low[u] = min(low[u], low[v]);
        else {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] > tin[u]) {
                bridges.push_back({u, v});
                isBridge[edgenum] = 1;
            }
        }
    }
}

void dfs1(int u) {
    vis[u] = 1;
    comp[u] = compnum;
    components[compnum].push_back(u);
    for (auto [v, edgenum] : adj[u]) {
        if(vis[v] or isBridge[edgenum]) continue;
        dfs1(v);
    }
}

void dfs2(int u, int par) {
    if(u == b) {
        flag |= goldNode[u];
        //return;
    }
    for (auto [v, edgenum] : bridgeTree[u]) if(v != par) {
        if(!goldNode[v]) goldNode[v] = goldEdge[edgenum];
        if(!goldNode[v]) goldNode[v] = goldNode[u];
        dfs2(v, u);
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    clear(n);
    edges.push_back({-1, -1}); // for 1 based indexing
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
        edges.push_back({u, v});
        goldEdge[i] = w;
    }
    for (int i = 1; i <= n; i++) if(!vis[i]) dfs(i, 0);
    for (int i = 1; i <= n; i++) vis[i] = 0;
    for (int i = 1; i <= n; i++) if(!vis[i]) {
        ++compnum;
        dfs1(i);
    }

    for (int i = 1; i <= m; i++) {
        if(!isBridge[i]) {
            if(goldNode[comp[edges[i].first]]) continue;
            goldNode[comp[edges[i].first]] = goldEdge[i]; 
        } else {
            int u = comp[edges[i].first], v = comp[edges[i].second];
            bridgeTree[u].push_back({v, i});
            bridgeTree[v].push_back({u, i});
        }
    }
    cin >> a >> b;
    a = comp[a], b = comp[b];
    for (int i = 1; i <= n; i++) vis[i] = 0;
    dfs2(a, 0);
    cout << (flag ? "YES" : "NO") << '\n';
    //https://codeforces.com/problemset/problem/652/E
}
    
int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1, tc = 1; 
    //cin >> t;
    while(t--) {
        //cout << "Case " << tc << ": ";
        solve();
        tc++;
    }
}
