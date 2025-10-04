<div align="center">

# My CP Snippet

Ready-to-use C++ templates for competitive programming with a lightweight debug helper and VS Code snippets.

</div>

---

## Table of contents

- Getting started
- Debugging helper (dout)
- Included utilities
- Folder contents

---

## Getting started

1) Use a snippet
   - In VS Code, create a new C++ file and type `cpp` or `cp`, then press Tab to expand.
   - If snippets don't appear, copy the two `.code-snippets` files into your workspace's `.vscode/` folder or import via "User Snippets".

2) Build and run (local)

```bash
g++ -std=c++17 -O2 your_file.cpp -o app
./app
```

3) Online Judge
   - Most judges define `ONLINE_JUDGE` for you. If you need to disable debug locally, compile with:

```bash
g++ -std=c++17 -O2 -DONLINE_JUDGE your_file.cpp -o app
```

> Tip: Keep `debugger.cpp` next to your source file or configure your include paths accordingly.

---

## Debugging helper (dout)

Include the debug helper only for local runs:

```cpp
#ifndef ONLINE_JUDGE
#include "debugger.cpp"
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = [", _print(__VA_ARGS__)
#else
#define dout(...) ((void)0)
#endif
```

Usage examples:

```cpp
int n = 5; vector<int> a = {1,2,3};
dout(n);            // Line:XX [n] = [5]
dout(n, a);         // Line:XX [n, a] = [5, [1, 2, 3]]
```

`debugger.cpp` prints most STL containers, pairs, tuples, stacks, queues, and priority_queues.

---

## Included utilities

- Fast IO boilerplate, RNG: `mt19937_64 rng(...)` and `gen_random(l, r)`
- `pbit(x)` to pretty-print bits of an integer
- PBDS ordered multiset alias `oset` (from `<ext/pb_ds/...>`), plus a hash-table alias `ht`
- Helpers: `smin(a,b)` and `smax(a,b)`
- Macro `#define int long long` for quick 64-bit arithmetic

> Note: If `#define int long long` causes issues (interop with libraries), use `using ll = long long;` instead and type variables explicitly as `ll`.

---

## Folder contents

- `simple snippet.cpp` — Single-file template (no testcase loop). Minimal main with fast IO, helpers, and utilities.
- `with testcase snippet.cpp` — Template with `Solve()` and a testcase loop: `int tc; cin >> tc;` then iterate.
- `debugger.cpp` — Debug printers used by the `dout(...)` macro (prints line number, names, and values). Automatically disabled on online judges via `ONLINE_JUDGE`.
- `checkDebugger.cpp` — Tiny smoke test for the debug helper.
- `Simple snippet.code-snippets` — VS Code workspace snippet, trigger: `cpp` (without testcase).
- `With TestCase.code-snippets` — VS Code workspace snippet, trigger: `cp` (with testcase).

---

That's it — expand a snippet, code your solution, use `dout(...)` locally, and ship clean output to the judge.

