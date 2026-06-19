#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define F first
#define S second
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
 
const int N = 1e6 + 1;
vector<int> cnt(N);
int B; ll curans;
 
// struct tup {
//     int l, r, ind, block;
// };
 
bool cmp(tup &a, tup &b) {
    if(a[3] != b[3]) return a[3] < b[3];
    return a[1] < b[1];
}
  
void add(int ind, vector<int> &ar) {
    int val = ar[ind];
    curans -= 1ll * cnt[val] * cnt[val] * val;
    cnt[val]++;
    curans += 1ll * cnt[val] * cnt[val] * val;
}
 
void remove(int ind, vector<int> &ar) {
    int val = ar[ind];
    curans -= 1ll * cnt[val] * cnt[val] * val;
    cnt[val]--;
    curans += 1ll * cnt[val] * cnt[val] * val;
}
 
ll get_answer() {
    return curans;
}
 
void solve(int tc) {
    int n, q; cin >> n >> q;
    vector<int> ar(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> ar[i];
    }

    B = sqrt(n);
    if(B * B < n) ++B;
 
    vector<tup> qr(q);
    for (int i = 0; i < q; ++i) {
        cin >> qr[i][0] >> qr[i][1];
        qr[i][2] = i + 1;
        qr[i][3] = qr[i][0] / B; // Precompute here!
    }
 
    
    sort(qr.begin(), qr.end(), cmp);
    // for (int i = 1; i <= n; ++i) {
    //     cout << ar[i] << " \n"[i == n];
    // }
 
    vector<ll> ans(q + 1);
    int mo_left = 1, mo_rt = 0;
    
    for (auto [l, r, ind, block] : qr) {
        while(mo_rt < r) {
            mo_rt++;
            add(mo_rt, ar);
        }
 
        while(mo_rt > r) {
            remove(mo_rt, ar);
            mo_rt--; 
        }
 
        while(mo_left > l) {
            mo_left--;
            add(mo_left, ar);
        }
 
        while(mo_left < l) { 
            remove(mo_left, ar);
            mo_left++; 
        } 
 
        ans[ind] = curans;
    }
    for (int i = 1; i <= q; ++i) cout << ans[i] << "\n";
    //https://codeforces.com/contest/86/problem/D
}
 
int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1, tc = 0; //cin >> t;
    while (t--) solve(++tc);
}
