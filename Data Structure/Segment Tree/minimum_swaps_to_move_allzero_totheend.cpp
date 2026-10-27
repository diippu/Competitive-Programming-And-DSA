#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define F first
#define S second
#define int long long
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
    int ans, zero, one, revans;
    node() {
        ans = zero = one = revans = 0;
    }
};

const int N = 2e5 + 5;
const ll inf = (ll) 1e18;
vector<node> seg (4 * N);
vector<int> lazy(4 * N, 0); 

void push(int ind, int al, int ar) {
    if(lazy[ind] == 0) return;

    swap(seg[ind].zero, seg[ind].one);
    swap(seg[ind].ans, seg[ind].revans);

    if(al != ar) {
        lazy[2 * ind] ^= 1;
        lazy[2 * ind + 1] ^= 1;
    }
    lazy[ind] = 0;
}

node merge(node a, node b) {
    node cur;
    cur.ans = a.ans + b.ans + a.zero * b.one;
    cur.revans = a.revans + b.revans + a.one * b.zero;
    cur.zero = a.zero + b.zero;
    cur.one = a.one + b.one;
    return cur;
}

void build(int ind, int al, int ar, string &s) {
    lazy[ind] = 0;
    if(al == ar) {
        if(s[al] == '0') seg[ind].zero = 1;
        else seg[ind].one = 1;
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

    if(r < al || l > ar) {
       return;
    }

    int mid = (al + ar) / 2;
    update(2 * ind, al, mid, l, r);
    update(2 * ind + 1, mid + 1, ar, l, r);
    seg[ind] = merge(seg[2 * ind], seg[2 * ind + 1]);
}

void solve(int tc) {
    int n, q; cin >> n;
    
    string s; cin >> s;
    s = '#' + s;
 
    build(1, 1, n, s);
    cin >> q;
    
    for (int i = 1; i <= q; ++i) {
        int l, r; 
        cin >> l >> r;

        update(1, 1, n, l, r);
        cout << seg[1].ans << '\n';
    }
    //https://www.hackerrank.com/contests/srbd-code-contest-2025-round-1/challenges/string-swap-4/problem
}

int32_t main() {
    ios_base::sync_with_stdio(false);cin.tie(0); 
    int t = 1, tc = 0; //cin >> t;
    while(t--) solve(++tc); 
}
