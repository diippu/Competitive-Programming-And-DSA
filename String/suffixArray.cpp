#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define F first
#define S second
using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using lll = __int128;
using pii = array<ll, 2>;
using tup = array<int, 3>;
template <typename T>
using order_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N = 8e5 + 10;
const int LG = 20;

void induced_sort(const vector<int> &vec, int val_range, vector<int> &SA, const vector<bool> &sl, const vector<int> &lms_idx) {
  vector<int> l(val_range, 0), r(val_range, 0);
  for (int c : vec) {
    if (c + 1 < val_range) ++l[c + 1];
    ++r[c];
  }
  partial_sum(l.begin(), l.end(), l.begin());
  partial_sum(r.begin(), r.end(), r.begin());
  fill(SA.begin(), SA.end(), -1);
  for (int i = lms_idx.size() - 1; i >= 0; --i)
    SA[--r[vec[lms_idx[i]]]] = lms_idx[i];
  for (int i : SA)
    if (i >= 1 && sl[i - 1]) {
      SA[l[vec[i - 1]]++] = i - 1;
    }
  fill(r.begin(), r.end(), 0);
  for (int c : vec)
    ++r[c];
  partial_sum(r.begin(), r.end(), r.begin());
  for (int k = SA.size() - 1, i = SA[k]; k >= 1; --k, i = SA[k])
    if (i >= 1 && !sl[i - 1]) {
      SA[--r[vec[i - 1]]] = i - 1;
    }
}

vector<int> SA_IS(const vector<int> &vec, int val_range) {
  const int n = vec.size();
  vector<int> SA(n), lms_idx;
  vector<bool> sl(n);
  sl[n - 1] = false;
  for (int i = n - 2; i >= 0; --i) {
    sl[i] = (vec[i] > vec[i + 1] || (vec[i] == vec[i + 1] && sl[i + 1]));
    if (sl[i] && !sl[i + 1]) lms_idx.push_back(i + 1);
  }
  reverse(lms_idx.begin(), lms_idx.end());
  induced_sort(vec, val_range, SA, sl, lms_idx);
  vector<int> new_lms_idx(lms_idx.size()), lms_vec(lms_idx.size());
  for (int i = 0, k = 0; i < n; ++i)
    if (!sl[SA[i]] && SA[i] >= 1 && sl[SA[i] - 1]) {
      new_lms_idx[k++] = SA[i];
    }
  int cur = 0;
  SA[n - 1] = cur;
  for (size_t k = 1; k < new_lms_idx.size(); ++k) {
    int i = new_lms_idx[k - 1], j = new_lms_idx[k];
    if (vec[i] != vec[j]) {
      SA[j] = ++cur;
      continue;
    }
    bool flag = false;
    for (int a = i + 1, b = j + 1;; ++a, ++b) {
      if (vec[a] != vec[b]) {
        flag = true;
        break;
      }
      if ((!sl[a] && sl[a - 1]) || (!sl[b] && sl[b - 1])) {
        flag = !((!sl[a] && sl[a - 1]) && (!sl[b] && sl[b - 1]));
        break;
      }
    }
    SA[j] = (flag ? ++cur : cur);
  }
  for (size_t i = 0; i < lms_idx.size(); ++i)
    lms_vec[i] = SA[lms_idx[i]];
  if (cur + 1 < (int)lms_idx.size()) {
    auto lms_SA = SA_IS(lms_vec, cur + 1);
    for (size_t i = 0; i < lms_idx.size(); ++i) {
      new_lms_idx[i] = lms_idx[lms_SA[i]];
    }
  }
  induced_sort(vec, val_range, SA, sl, new_lms_idx);
  return SA;
}
vector<int> suffix_array(const string &s, const int LIM = 128) {
  vector<int> vec(s.size() + 1);
  copy(begin(s), end(s), begin(vec));
  vec.back() = '!';
  auto ret = SA_IS(vec, LIM);
  //ret.erase(ret.begin()); //for deleting special character
  //ret.erase(ret.begin()); //there is two special character for this problem 
  return ret;
}

struct SuffixArray {
  int n;
  string s;
  vector<int> sa, rank, lcp;
  vector<vector<int>> t;
  vector<int> lg;
  SuffixArray() {}
  SuffixArray(string _s) {
    n = _s.size() + 1;
    s = _s;
    sa = suffix_array(s);
    rank.resize(n);
    for (int i = 0; i < n; i++) rank[sa[i]] = i;
    costruct_lcp();
    prec();
    build();
  }
  void costruct_lcp() {
    int k = 0;
    lcp.resize(n + 1, 0);//can be resized with n - 1, lcp[i] = lcp(i, i + 1);
    for (int i = 0; i < n; i++) {
      if (rank[i] == n - 1) {
        k = 0;
        continue;
      }
      int j = sa[rank[i] + 1];
      while (i + k < n && j + k < n && s[i + k] == s[j + k])  k++;
      lcp[rank[i]] = k;
      if (k)  k--;
    }
  }
  void prec() {
    lg.resize(n, 0);
    for (int i = 2; i < n; i++) lg[i] = lg[i / 2] + 1;
  }
  void build() {
    int sz = n;
    t.resize(sz);
    for (int i = 0; i < sz; i++) {
      t[i].resize(LG);
      t[i][0] = lcp[i];
    }
    for (int k = 1; k < LG; ++k) {
      for (int i = 0; i + (1 << k) - 1 < sz; ++i) {
        t[i][k] = min(t[i][k - 1], t[i + (1 << (k - 1))][k - 1]);
      }
    }
  }
  int query(int l, int r) { // minimum of lcp[l], ..., lcp[r]
    int k = lg[r - l + 1];
    return min(t[l][k], t[r - (1 << k) + 1][k]);
  }
  int get_lcp(int i, int j) { // lcp of suffix starting from i and j
    if (i == j) return n - i;
    int l = rank[i], r = rank[j];
    if (l > r) swap(l, r);
    return query(l, r - 1);
  }
};

void solve(int tc) {
    int n, m, q; cin >> n >> m >> q;
    string s, t; cin >> s >> t;
    t = t + '$' + s;
    SuffixArray sa(t);
    int sz = (int) sa.sa.size();

    int l = 0, r = 0;
    vector<int> v(m);
    for (int i = 2; i < sz; i++) {
        if(sa.sa[i] > m) {
            l = i;
            continue;
        }
        r = max(i + 1, r);
        while(r < sz) {
            if(sa.sa[r] > m) break;
            else r++;
        }
        if(l) v[sa.sa[i]] = sa.get_lcp(sa.sa[l], sa.sa[i]);
        if(r < sz) v[sa.sa[i]] = max(v[sa.sa[i]], sa.get_lcp(sa.sa[r], sa.sa[i]));
    }

    int st[LG + 1][m + 10];
    copy(v.begin(), v.end(), st[0]);
    for (int i = 1; i <= LG; i++)
        for (int j = 0; j + (1 << i) <= m; j++)
            st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
        
    while(q--) {
        int ql, qr; cin >> ql >> qr;
        ql--, qr--;
        int l = 1, r = qr - ql + 1, mid, ans = 0;
        while(l <= r) {
            mid = l + (r - l) / 2;
            int L = ql, R = qr - mid + 1;
            int i = sa.lg[R - L + 1];
            int mn = min(st[i][L], st[i][R - (1 << i) + 1]);
            if(mn >= mid) ans = mid, l = mid + 1;
            else r = mid - 1;
        }
        cout << ans << '\n';
    }
    //https://codeforces.com/gym/105973/problem/H
    //video : https://www.youtube.com/watch?v=Lu5sByCfPvE
    //ultimateTopicList: https://youkn0wwho.academy/topic-list/suffix_array
    //cpAlgorithm: https://cp-algorithms.com/string/suffix-array.html
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int t = 1, tc = 0; cin >> t;
    while(t--) solve(++tc);
}
