#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int B = 20;
struct node {
    int sz;
    node *nxt[2];
    node() {
        nxt[0] = nxt[1] = NULL;
        sz = 0;
    }
} *root;

void insert(int val) {
    node *cur = root;
    cur -> sz++;
    for (ll i = B - 1; i >= 0; --i) {
        int b = val >> i & 1;
        if(cur -> nxt[b] == NULL) cur -> nxt[b] = new node();
        
        cur  = cur -> nxt[b];
        cur -> sz++;
    }
}

int query_max(int val) { 
    //return maximum of val ^ x(x is already inserted)
    int ans = 0;
    node *cur = root;
    for (int i = B - 1; i >= 0; --i) {
        int b = val >> i & 1;
        if(cur -> nxt[!b] != NULL) ans += (1 << i), cur = cur -> nxt[!b];
        else cur = cur -> nxt[b];
    }
    return ans;
}

int query_min(int val) { 
    //return minimum of val ^ x(x is already inserted)
    int ans = 0;
    node *cur = root;
    for (int i = B - 1; i >= 0; --i) {
        int b = val >> i & 1;
        if(cur -> nxt[b] != NULL) cur = cur -> nxt[b];
        else ans += (1 << i), cur = cur -> nxt[!b]; 
    }
    return ans;
}

int query(ll val, ll k) { 
    //return number of values x which satisfy val ^ x < k(x is already inserted)
    int ans = 0;
    node *cur = root;
    for (ll i = B - 1; i >= 0; --i) {
        int bit1 = val >> i & 1;
        int bit2 = k >> i & 1;

        if(bit2 == 0) {
            if(cur -> nxt[bit1] != NULL) cur = cur -> nxt[bit1];
            else break;
        } else {
            if(cur -> nxt[bit1] != NULL) ans += (cur -> nxt[bit1]) -> sz;
            if(cur -> nxt[!bit1] != NULL) cur = cur -> nxt[!bit1];
            else break;
        }
    }
    return ans;
}

void solve(int tc) {
    int n; ll k; cin >> n >> k;
    vector<int> v(n + 5);
    for (int i = 1; i <= n; ++i) cin >> v[i];

    root = new node();
    insert(0);

    ll ans = 0, pref_xr = 0;
    for (int i = 1; i <= n; ++i) {
        pref_xr ^= v[i];
        ans += query(pref_xr, k);

        insert(pref_xr);  
    }
    cout << ans << '\n';

    //problem: https://www.spoj.com/problems/SUBXOR/
    
    //learning materials: 
    //(a) https://threadsiiithyderabad.quora.com/Tutorial-on-Trie-and-example-problems
    //(b) https://www.youtube.com/playlist?list=PLgUwDviBIf0pcIDCZnxhv0LkHf5KzG9zp
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1, tc = 0; cin >> t;
    while(t--) solve(++tc);
}
