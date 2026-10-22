# All Nim Games Variation And Grundy Number
---

## All Types

| Game Type | Allowed Move | Winning Condition (1st Player Wins) |
| :--- | :--- | :--- |
| **1. Standard Nim** | Remove `1 ≤ k ≤ a[i]` stones from pile `i` (last move wins) | `a[1] ⊕ a[2] ⊕ ... ⊕ a[n] ≠ 0` |
| **2. Misere Nim** | Remove `1 ≤ k ≤ a[i]` stones from pile `i` (**last move loses**) | If all `a[i] == 1`: `n % 2 == 0`<br>If any `a[i] > 1`: `a[1] ⊕ a[2] ⊕ ... ⊕ a[n] ≠ 0` |
| **3. Bogus (Poker) Nim** | Remove stones **OR add(finite moves)** stones to a pile | `a[1] ⊕ a[2] ⊕ ... ⊕ a[n] ≠ 0` (Additions are reversible) |
| **4. Staircase Nim** | Move `k ≥ 1` stones from step `i` to step `i - 1` | `a[1] ⊕ a[3] ⊕ a[5] ⊕ ... ≠ 0` (XOR only **odd** steps) |
| **5. Sprague-Grundy** | Any impartial game with restricted moves | `g(a[1]) ⊕ g(a[2]) ⊕ ... ⊕ g(a[n]) ≠ 0` |

---

## 1. Standard Nim Game

### Rules
- There are `n` piles of stones with sizes `a[1], a[2], ..., a[n]`.
- Players take turns choosing **one** pile and removing **at least one** stone from it.
- **Normal Play Convention:** The player who takes the **last stone wins** (the player with no valid moves left loses).

### Key Concept & Intuition (Bouton's Theorem)
Define the **Nim-sum** `S` as the bitwise XOR sum of all pile sizes:

```text
S = a[1] ⊕ a[2] ⊕ ... ⊕ a[n]
```

- **Winning State (`S ≠ 0`):** The current player has a winning move. There is always a pile `a[i]` whose size can be reduced to `a'[i] = a[i] ⊕ S < a[i]` (specifically, any pile that has a `1` at the most significant set bit of `S`), making the new XOR sum `0`.
- **Losing State (`S == 0`):** Any valid move from `S == 0` changes exactly one pile `a[i]`, which is guaranteed to make the new XOR sum non-zero (`S' ≠ 0`). And the terminal state `(0, 0, ..., 0)` has `S == 0`.

### C++ Snippet
```cpp
bool isWinningStandardNim(const vector<long long>& a) {
    long long xor_sum = 0;
    for (long long x : a) {
        xor_sum ^= x;
    }
    return xor_sum != 0; // true = 1st player wins, false = 2nd player wins
}
```

---

## 2. Misere Nim

### Rules
- Identical to Standard Nim, **except** for the winning condition:
- **Misere Play Convention:** The player who is forced to take the **last stone loses**.

### Key Concept & Intuition
There are only **two cases** to check:
1. **Case 1 (All piles have size `1`):** Neither player has any choice—every turn removes exactly one pile of size `1`.
   - If the number of piles `n` is **even** (`S == 0`), the 1st player wins (2nd player is forced to take the last stone).
   - If `n` is **odd** (`S == 1`), the 1st player loses.
2. **Case 2 (At least one pile has size `> 1`):** The winning condition is **identical to Standard Nim** (`S ≠ 0`).
   - *Why?* The player in the winning position plays just like Standard Nim until only **one** pile of size `> 1` remains (and some number of `1`-stone piles). At that point, the winning player either reduces that last `> 1` pile to `1` or to `0` so that an **odd** number of `1`-stone piles is left for the opponent.

### C++ Snippet
```cpp
bool isWinningMisereNim(const vector<long long>& a) {
    long long xor_sum = 0;
    bool all_ones = true;
    for (long long x : a) {
        xor_sum ^= x;
        if (x > 1) all_ones = false;
    }
    if (all_ones) {
        return xor_sum == 0; // Even number of 1s -> 1st player wins
    }
    return xor_sum != 0;     // Same as Standard Nim
}
```

---

## 3. Bogus Nim (Poker Nim)

### Rules
- Same as Standard Nim, but on a turn a player may either:
  1. **Remove** `k ≥ 1` stones from a pile (standard move), OR
  2. **Add** `k ≥ 1` stones to a pile (up to a finite limit of stones/additions so the game must terminate).
- The player who cannot make a move loses.

### Key Concept & Intuition
- Adding stones is a **Bogus (Reversible) Move**.
- Suppose Player 1 is in a winning position (`S == 0` after Player 1's move). If Player 2 **adds** `k` stones to pile `i`, Player 1 can immediately **remove** those exact `k` stones from pile `i` on the very next turn!
- This restores the exact previous state with `S == 0`. Therefore, the ability to add stones does not change the winner at all.
- **Winning Condition:** Identical to Standard Nim:

```text
a[1] ⊕ a[2] ⊕ ... ⊕ a[n] ≠ 0
```

---

## 4. Staircase Nim

### Rules
- There is a staircase with `n` steps indexed `1, 2, ..., n` from bottom to top, and the ground is step `0`.
- Step `i` initially contains `a[i]` stones.
- In one move, a player chooses any step `i ≥ 1` and moves `k ≥ 1` stones one step down: from step `i` to step `i - 1`.
- Stones on the ground (step `0`) cannot be moved further. The player who cannot make a move loses.

### Visual Diagram
```text
                        [a_4] (Even)
                        +-------+
                [a_3] (ODD)     |
                +-------+       |
        [a_2] (Even)    |       |
        +-------+       |       |
[a_1] (ODD)     |       |       |
+-------+       |       |       |
|Step 1 |Step 2 |Step 3 |Step 4 |
+-------+-------+-------+-------+
Step 0 (Ground - Stones here are out of the game)

  * Move from ODD  -> EVEN (e.g., Step 3 -> Step 2): Removes stones from Odd steps.
  * Move from EVEN -> ODD  (e.g., Step 4 -> Step 3): Adds stones to Odd steps (Bogus move!).
```

### Key Concept & Intuition
Group the steps into **Odd Steps** (`1, 3, 5, ...`) and **Even Steps** (`2, 4, 6, ...`):
1. **Moving `k` stones from an Odd step (`2m - 1`) to an Even step (`2m - 2`):** Decreases the stone count of the odd step by `k`. This acts exactly like removing `k` stones in Standard Nim.
2. **Moving `k` stones from an Even step (`2m`) to an Odd step (`2m - 1`):** Increases the stone count of the odd step `2m - 1` by `k`. This is a **Bogus Nim addition**! The other player can immediately counter it by moving those exact `k` stones from step `2m - 1` down to step `2m - 2` (another even step), leaving all odd steps unchanged.
3. **stones from even files don't matter cause eventually it goes to the ground by mirror move**

### Winning Condition
Staircase Nim is equivalent to **Standard Nim played ONLY on the ODD steps**:

```text
S_odd = a[1] ⊕ a[3] ⊕ a[5] ⊕ ... ≠ 0
```

### C++ Snippet
```cpp
// steps[] is 1-indexed: steps[1], steps[2], ..., steps[n]
bool isWinningStaircaseNim(const vector<long long>& steps, int n) {
    long long xor_odd = 0;
    for (int i = 1; i <= n; i += 2) {
        xor_odd ^= steps[i];
    }
    return xor_odd != 0;
}
```

---

## 5. Sprague-Grundy Theorem & Grundy Numbers

### Core Definitions
1. **MEX (Minimum Excluded Value):** For a set of non-negative integers `S`, `mex(S)` is the smallest non-negative integer **not** present in `S`.
   - `mex({}) = 0`
   - `mex({0, 1, 3}) = 2`
   - `mex({1, 2, 3}) = 0`
2. **Grundy Number (Nim-value) `g(u)`:** Every state `u` of a single-pile impartial game is equivalent to a Standard Nim pile of size `g(u)`:
   - If `u` is a **terminal state** (no moves possible): `g(u) = 0`.
   - Otherwise, if `u` can transition to states `v_1, v_2, ..., v_k`:

```text
g(u) = mex({ g(v_1), g(v_2), ..., g(v_k) })
```

3. **Sprague-Grundy Theorem:** If a game consists of `N` independent subgames (piles) with states `a[1], a[2], ..., a[N]`, the composite game has Grundy value:

```text
G = g(a[1]) ⊕ g(a[2]) ⊕ ... ⊕ g(a[N])
Be careful what we have to find mex/xor
```

   - **1st Player Wins** if and only if `G ≠ 0`.
   - **2nd Player Wins** if and only if `G == 0`.

---

### The Pattern-Finding Technique
In many problems, pile sizes can be as large as `a[i] ≤ 10^18`, making `O(a[i])` DP impossible.
1. **Step 1:** Write a simple brute-force recursive `mex` function to print `g(x)` for small values (`x = 0` to `30`).
2. **Step 2:** Inspect the printed table to spot periodicity, division patterns, or bitwise rules.
3. **Step 3:** Implement the fast `O(1)` or `O(log a[i])` formula for `g(x)`.

---

### Problem: Removing at Most Half the Stones (UVa 1482 - Playing With Stones)

#### Problem Summary
- There are `N` (`1 ≤ N ≤ 100`) piles of stones with sizes `a[1], a[2], ..., a[N]` (`1 ≤ a[i] ≤ 2 * 10^18`).
- In one turn, a player chooses one pile of size `x` and removes `k` stones such that:

```text
1 ≤ k ≤ ⌊x / 2⌋
```





- The player who cannot make any move loses. Determine if the first player has a winning move (`YES` or `NO`).

---

#### Step 1: Brute-Force Small Grundy Values to Find the Pattern
`g(x)` for `x = 1` to `12`:

```text
x  | Max Remove (x/2) | Reachable States x      | Reachable g(x)       | g(x) = mex(...)
---+------------------+--------------------------+-----------------------+----------------
1  | 0                | None                     | {}                    | 0
2  | 1                | {1}                      | {0}                   | 1
3  | 1                | {2}                      | {1}                   | 0
4  | 2                | {3, 2}                   | {0, 1}                | 2
5  | 2                | {4, 3}                   | {2, 0}                | 1
6  | 3                | {5, 4, 3}                | {1, 2, 0}             | 3
7  | 3                | {6, 5, 4}                | {3, 1, 2}             | 0
8  | 4                | {7, 6, 5, 4}             | {0, 3, 1, 2}          | 4
9  | 4                | {8, 7, 6, 5}             | {4, 0, 3, 1}          | 2
10 | 5                | {9, 8, 7, 6, 5}          | {2, 4, 0, 3, 1}       | 5
11 | 5                | {10, 9, 8, 7, 6}         | {5, 2, 4, 0, 3}       | 1
12 | 6                | {11, 10, 9, 8, 7, 6}     | {1, 5, 2, 4, 0, 3}    | 6
```

#### Step 2: Observe the Pattern!
Look closely at the last column `g(x)`:
- **When `x` is EVEN:**
  - `g(2) = 1, g(4) = 2, g(6) = 3, g(8) = 4, g(10) = 5, g(12) = 6`
  - **Rule:** `g(x) = x / 2`
- **When `x` is ODD:**
  - `g(1) = 0 = g(0)`
  - `g(3) = 0 = g(1)`
  - `g(5) = 1 = g(2)`
  - `g(7) = 0 = g(3)`
  - `g(9) = 2 = g(4)`
  - `g(11) = 1 = g(5)`
  - **Rule:** `g(x) = g(⌊x / 2⌋)`

So to compute `g(x)` for any `x ≤ 2 * 10^18`, we simply divide `x` by `2` while `x` is odd, and once `x` becomes even, return `x / 2`!


