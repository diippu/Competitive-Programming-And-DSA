#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define F first
#define S second
using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using pii = array<int, 2>;
using tup = array<int, 3>;
template <typename T>
using order_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
 
const int N = 1e5 + 5;
const int mod = 1e9 + 7;
vector<ll> t(4 * N, 0), lazy(4 * N, 0);
 
void push(int ind, int al, int ar) {
    int mid = al + (ar - al) / 2;
    lazy[2 * ind] += lazy[ind]; 
    t[2 * ind] += (mid - al + 1) * lazy[ind];
    lazy[2 * ind + 1] += lazy[ind];
    t[2 * ind + 1] += (ar - mid) * lazy[ind];
    lazy[ind] = 0; 
}
 
void update(int ind, int al, int ar, int l, int r, int v) {
    if(r < al or l > ar) return;
    if(l <= al and ar <= r) {
        t[ind] += 1ll * (ar - al + 1) * v;
        lazy[ind] += v;
        return;
    }
 
    push(ind, al, ar);
    int mid = al + (ar - al) / 2;
    update(2 * ind, al, mid, l, r, v);
    update(2 * ind + 1, mid + 1, ar, l, r, v);
    t[ind] = (t[2 * ind] + t[2 * ind + 1]);
}
 
ll query(int ind, int al, int ar, int l, int r) {
    if(r < al or l > ar) return 0;
    if(l <= al and ar <= r) {
        return t[ind];
    }
 
    push(ind, al, ar);
    int mid = al + (ar - al) / 2;
    ll left = query(2 * ind, al, mid, l, r);
    ll rgt = query(2 * ind + 1, mid + 1, ar, l, r);
    return (left + rgt);
}
 
void solve(int tc) {
    int n, m; cin >> n >> m;
 
    for (int i = 1; i <= m; ++i) {
        int tp; cin >> tp;
        if(tp == 1) {
            int l, r, v; cin >> l >> r >> v;
            update(1, 1, n, ++l, r, v);
 
        } else {
            int l, r; cin >> l >> r;
            cout << query(1, 1, n, ++l, r) << '\n';
        }
    }
    //https://codeforces.com/edu/course/2/lesson/5/2/practice/contest/279653/problem/D
    // https://www.youtube.com/watch?v=NEG-SoyigGE
    //https://youkn0wwho.academy/topic-list/segment_tree
    //https://cp-algorithms.com/data_structures/segment_tree.html
}
 
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int t = 1, tc = 0; //cin >> t;
    while(t--) solve(++tc);
}
