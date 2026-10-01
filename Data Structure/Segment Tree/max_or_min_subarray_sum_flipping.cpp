#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define F first
#define S second
using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using lll = __int128;
using pii = array<int, 2>;
using tup = array<int, 3>;
template <typename T>
using order_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

struct node {
    ll maxans, sum, maxpref, maxsuf;
    ll minans, minpref, minsuf; 
    node() {
        maxans = sum = maxpref = maxsuf = 0;
        minans = minpref = minsuf = 0;
    }
};

const int N = 2e5 + 5;
const ll inf = (ll) 1e18;
vector<node> seg(4 * N);
vector<int> lazy(4 * N, 0); 

void push(int ind, int al, int ar) {
    if(lazy[ind] == 0) return;
    
    seg[ind].sum = -seg[ind].sum;
    
    ll tmp = seg[ind].maxpref;
    seg[ind].maxpref = -seg[ind].minpref;
    seg[ind].minpref = -tmp;

    tmp = seg[ind].maxsuf;
    seg[ind].maxsuf = -seg[ind].minsuf;
    seg[ind].minsuf = -tmp;

    tmp = seg[ind].maxans;
    seg[ind].maxans = -seg[ind].minans;
    seg[ind].minans = -tmp;

    if(al != ar) {
        lazy[2 * ind] ^= 1;
        lazy[2 * ind + 1] ^= 1;
    }
    lazy[ind] = 0;
}

node merge(node a, node b) {
    node cur;
    
    cur.sum = a.sum + b.sum;

    cur.maxans = max({a.maxans, b.maxans, a.maxsuf + b.maxpref});
    cur.maxpref = max({a.maxpref, a.sum + b.maxpref});
    cur.maxsuf = max({b.maxsuf, a.maxsuf + b.sum});
    
    cur.minans = min({a.minans, b.minans, a.minsuf + b.minpref});
    cur.minpref = min({a.minpref, a.sum + b.minpref});
    cur.minsuf = min({b.minsuf, a.minsuf + b.sum});
    return cur;
}

void build(int ind, int al, int ar, string &s) {
    lazy[ind] = 0;
    if(al == ar) {
        ll val = (s[al - 1] == '1') ? 1 : -1;
        seg[ind].sum = val;
        seg[ind].maxans = seg[ind].maxpref = seg[ind].maxsuf = max(0LL, val);
        seg[ind].minans = seg[ind].minpref = seg[ind].minsuf = min(0LL, val);
        return;
    }

    int mid = (al + ar) / 2;
    build(2 * ind, al, mid, s);
    build(2 * ind + 1, mid + 1, ar, s);
    seg[ind] = merge(seg[2 * ind], seg[2 * ind + 1]);
}

void update(int ind, int al, int ar, int l, int r) {
    push(ind, al, ar);
    if(l <= al && ar <= r) {
        lazy[ind] ^= 1;
        push(ind, al, ar);
        return;
    }
    if(r < al || l > ar) return;

    int mid = (al + ar) / 2;
    update(2 * ind, al, mid, l, r);
    update(2 * ind + 1, mid + 1, ar, l, r);
    seg[ind] = merge(seg[2 * ind], seg[2 * ind + 1]);
}

node query(int ind, int al, int ar, int l, int r) {
    push(ind, al, ar);
    if(l <= al && ar <= r) return seg[ind];
    if(l > ar || r < al) {
        node cur; 
        return cur;
    }

    int mid = (al + ar) / 2;
    node left = query(2 * ind, al, mid, l, r);
    node rt = query(2 * ind + 1, mid + 1, ar, l, r);
    return merge(left, rt);
}

void solve(int tc) {
    int n, q; cin >> n >> q;
    
    string s; cin >> s;
 
    build(1, 1, n, s);
    
    for (int i = 1; i <= q; ++i) {
        int t, l, r; 
        cin >> t >> l >> r;
        
        if (t == 1) {
            update(1, 1, n, l, r);
        } else {
            node res = query(1, 1, n, l, r);
            ll ans = max(abs(res.sum - res.maxans), abs(res.sum - res.minans));
            cout << ans << '\n';
        }
    }
}

//https://codeforces.com/gym/720778/problem/K
 
int32_t main() {
    ios_base::sync_with_stdio(false);cin.tie(0); 
    int t = 1, tc = 0; //cin >> t;
    while(t--) solve(++tc); 
}
