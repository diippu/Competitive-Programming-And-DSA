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
    ll sum;
    node() {
        sum = 0;
    }
};

const int N = 2e5 + 5;
const ll inf = (ll) 1e18;

vector<node> seg1(4 * N), seg2(4 * N);
vector<ll> lazy1(4 * N, 0), lazy2(4 * N, 0); 

ll calcu(int l, int r) {
    return 1ll * r * (r + 1) / 2 - 1ll * (l - 1) * l / 2;
}

void push(int ind, int al, int ar, int tp, vector<node> &seg, vector<ll> &lazy) {
    if(lazy[ind] == 0) return;

    if(tp == 1) seg[ind].sum += 1ll * (ar - al + 1) * lazy[ind];
    else seg[ind].sum += calcu(al, ar) * lazy[ind];
        
    if(al != ar) {
        lazy[2 * ind] += lazy[ind];
        lazy[2 * ind + 1] += lazy[ind];
    }
    lazy[ind] = 0;
}

node merge(node a, node b) {
    node cur;
    cur.sum = a.sum + b.sum;
    return cur;
}

void update(int ind, int al, int ar, int l, int r, int tp, ll val, vector<node> &seg, vector<ll> &lazy) {
    push(ind, al, ar, tp, seg, lazy);
    if(l <= al && ar <= r) {
        lazy[ind] += val;
        push(ind, al, ar, tp, seg, lazy);
        return;
    }

    if(r < al || l > ar) return;

    int mid = (al + ar) / 2;
    update(2 * ind, al, mid, l, r, tp, val, seg, lazy);
    update(2 * ind + 1, mid + 1, ar, l, r, tp, val, seg, lazy);
    seg[ind] = merge(seg[2 * ind], seg[2 * ind + 1]);
}

node query(int ind, int al, int ar, int l, int r, int tp, vector<node> &seg, vector<ll> &lazy) {
    push(ind, al, ar, tp, seg, lazy);
    if(l <= al && ar <= r) return seg[ind];
    if(l > ar || r < al) {
        node cur; 
        return cur;
    }

    int mid = (al + ar) / 2;
    node left = query(2 * ind, al, mid, l, r, tp, seg, lazy);
    node rt = query(2 * ind + 1, mid + 1, ar, l, r, tp, seg, lazy);
    return merge(left, rt);
}

void solve(int tc) {
    int n, q; cin >> n >> q;
    
    //query = xi * (i - l + 1);
    //query ans = xi * i - (l - 1) * xi
    //separate xi * i  and (l - 1) * xi

    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        update(1, 1, n, i, i, 1, x, seg1, lazy1);
        update(1, 1, n, i, i, 2, x, seg2, lazy2);
    }
    
    for (int i = 1; i <= q; ++i) {
        int t; cin >> t;
        
        if (t == 1) {
            int l, r, d; cin >> l >> r >> d;
            update(1, 1, n, l, r, 1, d, seg1, lazy1);
            update(1, 1, n, l, r, 2, d, seg2, lazy2);

        } else {
            int l, r; cin >> l >> r;
            ll res1 = query(1, 1, n, l, r, 1, seg1, lazy1).sum;
            ll res2 = query(1, 1, n, l, r, 2, seg2, lazy2).sum; 
            cout << res2 - 1ll * (l - 1) * res1 << '\n';
        }
    }
    //https://codeforces.com/edu/course/2/lesson/5/4/practice/contest/280801/problem/D
   
}


 
int32_t main() {
    ios_base::sync_with_stdio(false);cin.tie(0); 
    int t = 1, tc = 0; //cin >> t;
    while(t--) solve(++tc); 
}
