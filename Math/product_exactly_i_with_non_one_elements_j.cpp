#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
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

template<unsigned P> struct modint{
    unsigned v; static unsigned mod; modint() = default;
    template<class T> modint(T x) {x %= (signed)getmod(), v = x < 0 ? x + getmod() : x;}
    static unsigned getmod() {return P > 0 ? P : mod;}
    static void setmod(unsigned m) {mod = m;}
    modint operator+() const{return *this;}
    modint operator-() const{return modint(0) - *this;}
    static modint power(modint a, int b) {if (b < 0)return power(a, -b).inv(); modint res = 1; while (b) {if (b & 1)res *= a; a *= a; b >>= 1;} return res;}
    modint inv() const{return assert(v), power(*this, getmod() - 2);}
    modint & operator+=(const modint & q) {(v += q.v) < getmod() || (v -= getmod()); return *this;}
    modint & operator-=(const modint & q) {(v -= q.v) < getmod() || (v += getmod()); return *this;}
    modint & operator*=(const modint & q) {v = 1ull * v * q.v % getmod(); return *this;}
    modint &operator/=(const modint & q) {v = 1ull * v * q.inv().v % getmod(); return *this;}
    friend modint operator+(modint p, const modint & q) {return p += q;}
    friend modint operator-(modint p, const modint & q) {return p -= q;}
    friend modint operator*(modint p, const modint & q) {return p *= q;}
    friend modint operator/(modint p, const modint & q) {return p /= q;}
    friend bool operator==(const modint & p, const modint & q) {return p.v == q.v;}
    friend bool operator!=(const modint & p, const modint & q) {return p.v != q.v;}
    friend bool operator<(const modint & p, const modint & q) {return p.v < q.v;}
    friend bool operator>(const modint & p, const modint & q) {return p.v > q.v;}
    friend bool operator<=(const modint & p, const modint & q) {return p.v <= q.v;}
    friend bool operator>=(const modint & p, const modint & q) {return p.v >= q.v;}
    friend istream & operator>>(istream & is, modint & a) {int x; is >> x; x %= (signed)getmod(); a.v = x < 0 ? x + getmod() : x; return is;}
    friend ostream & operator<<(ostream & os, const modint & a) {os << a.v; return os;}
};
template<> unsigned modint<0>::mod = 998244353;
typedef modint<0> mint;

const int N = 1e5 + 5;
vector<int> d[N];
mint dp[20][N];

//dp[j][i] = number of arrays with product i which non-one elements are exactly j
//hocky-stick identity

void prec() {
    for (int i = 2; i < N; ++i) for (int j = i; j < N; j += i) {
        d[j].push_back(i);
    }
    //dp[0][1] = 1;
    for (int i = 2; i < N; ++i) dp[1][i] = 1;
    for (int j = 2; j <= 16; ++j) for (int i = 2; i < N; ++i) for (auto div : d[i]) {
        dp[j][i] += dp[j - 1][i / div];
    }
}

mint NCR(int n, int r) {
    if(r < 0 or r > n) return 0;
    mint p = 1, q = 1;
    for (int i = n, j = r; j >= 1; --j, --i) {
        p *= i, q *= j;
    }
    return p / q;
}

void solve(int tc) {
    int k, n; cin >> k >> n;
    //cout << NCR(5, 6) << '\n';
    vector<mint> ans(k + 5, n);
    for (int i = 2; i <= k; ++i) {
        mint curans = 0;
        for (int j = 1; j <= 16; ++j) {
            //cout << i << " " << j << " " << dp[j][i] << '\n';

            curans += NCR(n + 1, j + 1) * dp[j][i];
            //cout << ans << '\n';
        }
        ans[i] = curans;
        //cout << ans << " \n"[i == k];
    }
    for (int i = 1; i <= k; ++i) cout << ans[i] << " \n"[i == k];

    //https://codeforces.com/contest/2060/problem/F
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); prec();
    int t = 1, tc = 0; cin >> t;
    while (t--) solve(++tc);
}
