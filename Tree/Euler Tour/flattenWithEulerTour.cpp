#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using tup = tuple<int, int, int>;
using pii = pair<int, int>;
#define int long long

template <typename T>
using order_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N = 2e5 + 5;

vector<int> adj[N], flat(N), a(N), st(N), en(N);
int t;

class SGTree {
    vector<int> seg;
public: 
    SGTree(int n) {
        seg.resize(4 * n + 1);
    }

    void build(int ind, int low, int high, vector<int> &a) {
        if(low == high) {
            seg[ind] = a[low];
            return;
        }
        int mid = low + (high - low) / 2;
        build(2 * ind, low, mid, a);
        build(2 * ind + 1, mid + 1, high, a);
        seg[ind] = seg[2 * ind] + seg[2 * ind + 1];
    }

    void update(int ind, int low, int high, int pos, int val) {
        if(low == high) {
            seg[ind] = val;
            return;
        }
        int mid = low + (high - low) / 2;
        if(pos <= mid) update(2 * ind, low, mid, pos, val);
        else update(2 * ind + 1, mid + 1, high, pos, val);
        seg[ind] = seg[2 * ind] + seg[2 * ind + 1];
    }

    int query(int ind, int low, int high, int l, int r) {
        if(r < low || l > high) return 0;
        if(l <= low and r >= high) return seg[ind];
        int mid = low + (high - low) / 2;
        int left = query(ind * 2, low, mid, l, r);
        int right = query(ind * 2 + 1, mid + 1, high, l, r);
        return left + right;
    }
};

void dfs(int u, int p) {
    st[u] = ++t;;
    for (auto v : adj[u]) if(v != p) dfs(v, u);
    en[u] = t;
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 5);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++) flat[st[i]] = a[i];
    SGTree sg(t);
    sg.build(1, 1, t, flat);

    while(q--) {
        int type; cin >> type;
        if(type == 1) {
            int u, x;
            cin >> u >> x;
            sg.update(1, 1, t, st[u], x);
        } else {
            int u; 
            cin >> u;
            cout << sg.query(1, 1, t, st[u], en[u]) << '\n';
        } 
    }
    //https://cses.fi/problemset/task/1137
}
    
int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1, tc = 1;
    //cin >> t;
    for (int i = 1; i <= t; i++) {
        //cout << "Case #" << i << ": ";
        solve();
    }
}
