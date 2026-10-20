# Hockey-Stick Identity & nCr (mod M)

## 1. The Hockey-Stick Identity

In combinatorics, the **hockey-stick identity** (also known as the **Christmas stocking identity**, **boomerang identity**, **Fermat's identity**, or **Chu's Theorem**) states that for integers **n ≥ r ≥ 0**:

```text
C(r, r) + C(r + 1, r) + C(r + 2, r) + ... + C(n, r) = C(n + 1, r + 1)
```

Or in summation notation:

```text
  n
  ∑   C(i, r)  =  C(n + 1, r + 1)
i = r
```

### Visual Representation (Pascal's Triangle)
<img width="1210" height="398" alt="image" src="https://github.com/user-attachments/assets/822e2b63-c581-416e-b8c4-ed92843e13e5" />



```text
Row 0:                  1
Row 1:                1   1
Row 2:              1   2  [1]          <-- C(2,2) = 1
Row 3:            1   3  [3]  1         <-- C(3,2) = 3
Row 4:          1   4  [6]  4   1       <-- C(4,2) = 6
Row 5:        1   5 [10] 10   5   1     <-- C(5,2) = 10
Row 6:      1   6 [15] 20  15   6   1   <-- C(6,2) = 15
Row 7:    1   7  21 (35) 35  21   7   1 <-- C(7,3) = 35 (Sum)
```

> **Example (n = 6, r = 2):**
> - **Formula:** `C(2,2) + C(3,2) + C(4,2) + C(5,2) + C(6,2) = C(7,3)`
> - **Calculation:** `1 + 3 + 6 + 10 + 15 = 35`

---

## 2. C++ Code Template: nCr (mod M)

Using precomputed factorials and modular inverse factorials, we can evaluate any `nCr % M` query—including the Hockey-Stick Identity sum `ncr(n + 1, r + 1)`—in **O(1)** time after an **O(N)** precomputation.

```cpp
const int N = 1e6 + 10;
const int M = 1e9 + 7;
vector<int> fac(N), invf(N);

int binpow(int a, int b) {
    int res = 1;
    a %= M;
    while (b > 0) {
        if (b & 1) res = 1ll * res * a % M;
        a = 1ll * a * a % M;
        b >>= 1;
    }
    return res;
}

int ncr(int n, int r) {
    if (r > n || n < 0 || r < 0) return 0;

    int res = 1ll * fac[n] * invf[r] % M;
    return 1ll * res * invf[n - r] % M;
}

void precal() {
    fac[0] = 1;
    for (int i = 1; i < N; ++i) {
        fac[i] = 1ll * fac[i - 1] * i % M;
    }

    invf[N - 1] = binpow(fac[N - 1], M - 2);
    for (int i = N - 2; i >= 0; --i) {
        invf[i] = 1ll * invf[i + 1] * (i + 1) % M;
    }
}
```

---

## 3. Complexity Summary

| Function / Query | Time Complexity | Space Complexity | Description |
| :--- | :--- | :--- | :--- |
| `precal()` | `O(N + log M)` | `O(N)` | precomputes factorials and inverse factorials up to `N`. |
| `binpow(a, b)` | `O(log b)` | `O(1)` | binary exponentiation for `a^b % M`. |
| `ncr(n, r)` | `O(1)` | `O(1)` | computes `C(n, r) % M` in constant time. |
| **Hockey-Stick Sum** | `O(1)` | `O(1)` | computed directly by calling `ncr(n + 1, r + 1)`. |
