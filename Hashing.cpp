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

const int N = 2e5 + 10;
vector<int> p1(N, 1), p2(N, 1);
vector<int> inp1(N, 1), inp2(N, 1);
int b1 = 37, m1 = 1e9 + 7;
int b2 = 73, m2 = 998244341;

int modp(int i, int j, int m) {
    return 1ll * i * j % m;
}

int moda(int i, int j, int m) {
    return (i + j) % m;
}

int mods(int i, int j, int m) {
    return ((i - j) % m + m) % m;
}

vector<int> get_hash(string s, int b, int m, vector<int> p) {
    //hash vector of a string 1000456781 998244341 37 73
    int sz = s.size();
    s = '#' + s;//everything is 1 based indexing
    vector<int> hash(sz + 10);
    hash[0] = 0;
    hash[1] = (s[1] - 'a' + 1);
    for (int i = 1; i <= sz; i++) {
        int cur = modp(s[i] - 'a' + 1, p[i], m);
        hash[i] = moda(hash[i - 1], cur, m) % m;
    }
    return hash;
}

int getHashL_R(int l, int r, vector<int> &hash, vector<int> &inp, int m) {
     int hsh = mods(hash[r], hash[l - 1], m);
     hsh = modp(hsh, inp[l], m);
     return hsh;
}

int binpow(int a, int b, int m) {
    a %= m;
    int res = 1;
    while (b > 0) {
        if (b & 1) res = 1ll * res * a % m;
        a = 1ll * a * a % m;
        b >>= 1;
    }
    return res % m;
}

void pre() {
    //p[i] have power i - 1;
    for (int i = 2; i < N; i++) {
        p1[i] = modp(p1[i - 1], b1, m1);
        p2[i] = modp(p2[i - 1], b2, m2);
        inp1[i] = binpow(p1[i], m1 - 2, m1);
        inp2[i] = binpow(p2[i], m2 - 2, m2);
    }
}

void solve(int tc) {
    int n, k; cin >> n >> k;
    string s; cin >> s;
    s += s;
    n = s.size();

    vector<int> hash1 = get_hash(s, b1, m1, p1);
    vector<int> hash2 = get_hash(s, b2, m2, p2);

    set<pii> st;
    for (int i = 1; i + k - 1 <= n; ++i) {
          int hsh1 = getHashL_R(i, i + k - 1, hash1, inp1, m1);
          int hsh2 = getHashL_R(i, i + k - 1, hash2, inp2, m2);
          pii p = {hsh1, hsh2};
          st.insert(p);
    }

    reverse(s.begin(), s.end());

    hash1 = get_hash(s, b1, m1, p1);
    hash2 = get_hash(s, b2, m2, p2);

    for (int i = 1; i + k - 1 <= n; ++i) {
          int hsh1 = getHashL_R(i, i + k - 1, hash1, inp1, m1);
          int hsh2 = getHashL_R(i, i + k - 1, hash2, inp2, m2);
          pii p = {hsh1, hsh2};
          st.insert(p);
    }

    cout << st.size() << '\n';
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); pre();
    int t = 1, tc = 0; //cin >> t;
    while(t--) solve(++tc);
}
