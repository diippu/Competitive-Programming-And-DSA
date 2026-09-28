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
 
const int m = 1e9 + 7;
int binpow(int a, int b) {
    a %= m;
    int res = 1;
    while (b > 0) {
        if (b & 1) {
            res = 1ll * res * a % m;
        }
        a = 1ll * a *  a % m;
        b >>= 1;
    }
    return res;
}
 
void solve(int tc) {
    int n; cin >> n;
    int B = 21;
    vector<int> v(n), supmask(1 << B);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        supmask[x]++;
    }
 
    for (int i = 0; i < B; ++i) {
        for (int mask = (1 << B) - 1; mask >= 0; --mask) {
            if(!(mask & 1 << i)) supmask[mask] += supmask[mask ^ 1 << i];
        }
    }
 
    for (int mask = 0; mask < 1 << B; ++mask) {
        supmask[mask] = binpow(2, supmask[mask]);
    }
 
    for (int i = 0; i < B; ++i) {
        for (int mask = (1 << B) - 1; mask >= 0; --mask) {
            if(!(mask & 1 << i)) {
                supmask[mask] = (supmask[mask] - supmask[mask ^ 1 << i] + m) % m;
            }
        }
    }
    for (int i = 0; i <= n; ++i) cout << supmask[i] << " \n"[i == n]; 
    //cout << supmask[0] << '\n';
    //https://cses.fi/problemset/task/3141/
    //https://www.youtube.com/watch?v=mkiK_GCWX50
}
 
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int t = 1, tc = 0; //cin >> t;
    while(t--) solve(++tc);
}
