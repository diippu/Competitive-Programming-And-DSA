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

struct node {
    int len, cnt, lazy;
    bool lftblack, rtblack;
    node() {
        len = cnt = lftblack = rtblack = 0;
        lazy = -1; // -1 = no color, 0 = white, 1 = black
    }
};

const int N = 1e6 + 10;
const int shift = 5e5 + 1;
const int mod = 1e9 + 7;

vector<node> seg(4 * N);
 
void push(int ind, int al, int ar) {
    if(seg[ind].lazy == 0) {
        seg[ind].len = seg[ind].cnt = 0;
        seg[ind].lftblack = seg[ind].rtblack = 0;
    } else if(seg[ind].lazy == 1) {
        seg[ind].len = ar - al + 1; seg[ind].cnt = 1;
        seg[ind].lftblack = seg[ind].rtblack = 1;
    }

    if(al != ar && seg[ind].lazy != -1) {
        seg[2 * ind].lazy = seg[ind].lazy; 
        seg[2 * ind + 1].lazy = seg[ind].lazy;     
    } 
    seg[ind].lazy = -1;
}

node merge(node a, node b) {
    node cur;
    cur.len = a.len + b.len;
    cur.cnt = a.cnt + b.cnt - (a.rtblack && b.lftblack);
    cur.lftblack = a.lftblack;
    cur.rtblack = b.rtblack;
    cur.lazy = -1;
    return cur;
}
 
void update(int ind, int al, int ar, int l, int r, int v) {
    push(ind, al, ar);
    if(r < al or l > ar) return;
    if(l <= al and ar <= r) {
        seg[ind].lazy = v;
        push(ind, al, ar);
        return;
    }
 
    int mid = al + (ar - al) / 2;
    update(2 * ind, al, mid, l, r, v);
    update(2 * ind + 1, mid + 1, ar, l, r, v);

    seg[ind] = merge(seg[2 * ind], seg[2 * ind + 1]);
}
 
node query(int ind, int al, int ar, int l, int r) {
    push(ind, al, ar);
    if(r < al or l > ar) {
        node cur;
        return cur;
    }

    if(l <= al and ar <= r) {
        return seg[ind];
    }
 
    int mid = al + (ar - al) / 2;
    if(r <= mid) return query(2 * ind, al, mid, l, r);
    if(l > mid) return query(2 * ind + 1, mid + 1, ar, l, r);
    
    node left = query(2 * ind, al, mid, l, r);
    node rgt = query(2 * ind + 1, mid + 1, ar, l, r);
    return merge(left, rgt);
}
 
void solve(int tc) {
    int m; cin >> m;
    int st = 1, en = 2 * shift - 1;
 
    for (int i = 1; i <= m; ++i) {
        char c; cin >> c;
        int x, d, l, r; cin >> x >> d;
        l = x + shift, r = x + d + shift - 1;

        update(1, st, en, l, r, (c == 'B' ? 1 : 0));
        cout << seg[1].cnt << " " << seg[1].len << '\n';
    }

    //https://codeforces.com/edu/course/2/lesson/5/4/practice/contest/280801/problem/C
    
}
 
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int t = 1, tc = 0; //cin >> t;
    while(t--) solve(++tc);
}
