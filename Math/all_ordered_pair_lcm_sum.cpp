
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
///areakta lagbe ans[i] jeta shobar answer rakhbe dp[i][1] + dp[i][2]

const int N = 1e6 + 1;
const int M = 998244353;
vector<int> sum1(N), s(N), t(N), sum2(N), sq(N);

//s[i] prduct of a * b which gcd is multiple of i
//t[i] prduct of a * b which gcd is i

//f[i] number of pairs gcd as multiple of i
//g[i] number of pairs gcd as i


int binpow(int a, int b) {
  int res = 1;
  while(b > 0) {
    if(b & 1) res = 1ll * res * a % M;
    a = 1ll * a * a % M;
    b >>= 1;
  }
  return res;
}

void solve(int tc) {
  int n; cin >> n;
  vector<int> v(n + 5);
  for (int i = 1; i <= n; ++i) {
    cin >> v[i];

    sum1[v[i]] += v[i];
    sum1[v[i]] %= M;

    sum2[v[i]] += 1ll * v[i] * v[i] % M;
    sum2[v[i]] %= M;
  }

  for (int i = N - 1; i >= 1; --i) {
    s[i] = sum1[i];
    sq[i] = sum2[i];
    for (int j = 2 * i; j < N; j += i) {
      s[i] += sum1[j];
      s[i] %= M;

      sq[i] += sum2[j];
      sq[i] %= M;
    }
  }

  for (int i = N - 1; i >= 1; --i) {
    t[i] = 1ll * s[i] * s[i] % M;
    t[i] -= sq[i]; //ai * ai baad
    t[i] += M;
    t[i] %= M;

    t[i] = 1ll * t[i] * binpow(2, M - 2) % M; //ordered pair half

    for (int j = 2 * i; j < N; j += i) {
      t[i] -= t[j];
      t[i] += M;
      t[i] %= M;
    }
  }

  int ans = 0;
  for (int i = 1; i < N; ++i) {
    int curans = 1ll * t[i] * binpow(i, M - 2) % M;
    ans = (ans + curans) % M;
  }

  cout << ans << '\n';

  //https://atcoder.jp/contests/agc038/tasks/agc038_c
}
 
int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1, tc = 0; //cin >> t;
    while (t--) solve(++tc);
}
