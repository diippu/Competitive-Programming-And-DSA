#include<bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using tup = tuple<int, int, int>;
using ll = long long;

const int N = 2e5 + 5;
vector<int> parent(N), siz(N);

int findpar(int node) {
    if(node == parent[node]) return node;
    return parent[node] = findpar(parent[node]);
}
    
void unio(int u, int v) {
    u = findpar(u);
    v = findpar(v);
    if(u == v) return;
    parent[v] = u;
    siz[u] += siz[v];   
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<tup> edges;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({w, u, v});
    }
    int ans = 0;
    for (int i = 29; i >= 0; i--) {
        vector<tup> tmp;
        for (auto [w, u, v] : edges) {
            if(w & 1 << i) continue;
            tmp.push_back({w, u, v});
        }
        for (int j = 1; j <= n; j++) {
            siz[j] = 1;
            parent[j] = j;
        }
        int cnt = 0;
        for (auto [w, u, v] : tmp) {
            if(findpar(u) != findpar(v)) {
                unio(u, v);
                cnt++;
            }
        }
        if(cnt == n - 1) edges = tmp;
        else ans += 1 << i;
    }
    cout << ans << '\n';
    //https://codeforces.com/problemset/problem/1624/G
}
    
int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    cin >> t;
    while(t--) solve();
}
