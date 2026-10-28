#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define F first
#define S second
using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using pii = array<int, 2>;
using tup = array<int, 2>;
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

void solve(int tc) {
    int n; cin >> n;
    map<int, int> mp;

    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
      cin >> v[i];
      for (int j = 1; j * j <= v[i]; ++j) {
        if(v[i] % j) continue;
        mp[j] = __gcd(mp[j], v[i]);
        mp[v[i] / j] = __gcd(mp[v[i] / j], v[i]);
      }
    }

    int mini = *min_element(v.begin(), v.end()), ans = 1;
    for (auto [d, gc] : mp) {
      ans += ( d < mini && d == gc);
    }
    cout << ans << '\n';

    //https://atcoder.jp/contests/abc191/tasks/abc191_f
}
 
int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1, tc = 0; //cin >> t;
    while (t--) solve(++tc);
}
