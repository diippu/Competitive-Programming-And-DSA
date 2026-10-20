#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define F first
#define S second
#define int long long
using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using pii = array<int, 2>;
using tup = array<int, 4>;
using LL = __int128;
template <typename T>
using order_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T> using minheap = priority_queue<T, vector<T>, greater<T>>;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
// find_by_order() -> iterator to the k-th largest element (zero based)
// order_of_key() -> the number of items that are strictly smaller
// __builtin_popcount() -> number of ones
// __builtin_clz() -> number of leading 0bits from msb
// __builtin_ctz() -> number of leading 0bits from lsb

const int N = 1e6 + 10;
const int M = 1e9 + 7;
vector<int> fac(N), invf(N);

int binpow(int a, int b) {
    int res = 1;
    a %= M;
    while(b > 0) {
        if(b & 1) res = res * a % M;
        a = a * a % M;
        b >>= 1;
    }
    return res;
}

int ncr(int n, int r) {
    if(r > n || n < 0 || r < 0) return 0;

    int res = fac[n] * invf[r] % M;
    return res * invf[n - r] % M;
}

void precal() {
    fac[0] = 1;
    for (int i = 1; i < N; ++i) {
        fac[i] = fac[i - 1] * i % M;
    }

    invf[N - 1] = binpow(fac[N - 1], M - 2);
    for (int i = N - 2; i >= 0; --i) {
        invf[i] = invf[i + 1] * (i + 1) % M;
    }
}

void solve(int tc) {
    int n; cin >> n;

    int ans = 0;
    for (int i = 0; i <= n; ++i) {
        int x; cin >> x;
        ans = (ans + ncr(i + x, i + 1)) % M;
    }

    cout << ans << '\n';
    //https://codeforces.com/contest/1696/problem/E
}
 
int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    precal();
    int t = 1; //cin >> t;
    for (int tc = 1; tc <= t; ++tc) {
        //cout << "Case " << tc << ": "; 
        solve(tc);
    }
}
