#include<bits/stdc++.h>
using namespace std;
 
using ll = long long;
 
struct Manacher {
  vector<int> p[2];
  // p[1][i] = (max odd length palindrome centered at i) / 2 [floor division]
  // p[0][i] = same for even, it considers the right center
  // e.g. for s = "abbabba", p[1][3] = 3, p[0][2] = 2
  Manacher(string s) {
    int n = s.size();
    p[0].resize(n + 1);
    p[1].resize(n);
    for (int z = 0; z < 2; z++) {
      for (int i = 0, l = 0, r = 0; i < n; i++) {
        int t = r - i + !z;
        if (i < r) p[z][i] = min(t, p[z][l + t]);
        int L = i - p[z][i], R = i + p[z][i] - !z;
        while (L >= 1 && R + 1 < n && s[L - 1] == s[R + 1]) 
          p[z][i]++, L--, R++;
        if (R > r) l = L, r = R;
      }
    }
  }
  bool is_palindrome(int l, int r) {
    int mid = (l + r + 1) / 2, len = r - l + 1;
    return 2 * p[len % 2][mid] + len % 2 >= len;
  }
};
 
void solve(int tc) {
    string s; cin >> s;
    
    Manacher M(s);
 
    int n = s.size();
    vector<int> ans(n + 5);
 
    int r = 0;
 
    for (int i = 0; i < n; ++i) {
        int cur_r = M.p[0][i] + i - 1;
 
        r = max(r, i);
 
        while(r <= cur_r) {
            ans[r] = (r - i + 1) * 2;
            ++r;
        }
    }
 
    r = 0;
 
    for (int i = 0; i < n; ++i) {
        int cur_r = M.p[1][i] + i;
 
        r = max(r, i);
 
        while(r <= cur_r) {
            ans[r] = max(ans[r], (r - i) * 2 + 1);
            ++r;
        }
    }
 
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " \n"[i + 1 == n];
    }
}
 
int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t = 1, tc = 0; //cin >> t;
  while(t--) solve(++tc);
}
//https://cses.fi/problemset/task/3138/
