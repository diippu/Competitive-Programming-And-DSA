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

const int N = 1e5 + 1;
const int M = 1e8 + 7;
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

const int lim = (int) 1e10;

int cur_pftp(int a, int b) { //to find power
    int res = 1;
    for (int i = 1; i <= b; ++i) {
        res *= a;
        if(res > lim) return -1;
    }
    return res;
}

vector<int> pftp;

void count_perfect_power() {
    for (int i = 2; i < N; ++i) {
        for (int j = 2; j <= 33; ++j) {
            int cur_num = cur_pftp(i, j);
            if(cur_num != -1) pftp.push_back(cur_num);
            else break;
        }
    }
    
    sort(pftp.begin(), pftp.end());

    auto it = unique(pftp.begin(), pftp.end());
    pftp.resize(distance(pftp.begin(), it));
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

    count_perfect_power();
}

void solve(int tc) {
    int l, r; cin >> l >> r;

   //cout << pftp.size() << '\n';

   int n = upper_bound(pftp.begin(), pftp.end(), r) - upper_bound(pftp.begin(), pftp.end(), l - 1);

   //n = perfect power from l to r, then answer is the nth catalan number
   //cout << n << '\n';
   if(n == 0) {
        cout << "0\n";
        return;
   }

   int ans = binpow(n + 1, M - 2) * ncr(2 * n, n) % M;
   cout << ans << '\n';
}
 
int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    precal();
    int t = 1; cin >> t;
    for (int tc = 1; tc <= t; ++tc) {
        cout << "Case " << tc << ": "; 
        solve(tc);
    }
}
