## My CP Snippet

Ready-to-use C++ templates for competitive programming with a lightweight debug helper and VS Code snippets.

### What’s inside

- `simple snippet.cpp` — Single-file template (no testcase loop). Minimal main with fast IO, helpers, and utilities.
- `with testcase snippet.cpp` — Template with `Solve()` and a testcase loop: `int tc; cin >> tc;` then iterate.
- `debugger.cpp` — Debug printers used by the `dout(...)` macro (prints line number, names, and values). Automatically disabled on online judges via `ONLINE_JUDGE`.
- `checkDebugger.cpp` — Tiny smoke test for the debug helper.
- `Simple snippet.code-snippets` — VS Code workspace snippet, trigger: `cpp` (without testcase).
- `With TestCase.code-snippets` — VS Code workspace snippet, trigger: `cp` (with testcase).

### Quick start

1) Use a snippet
- In VS Code, create a new C++ file and type `cpp` or `cp`, then press Tab to expand.
- If snippets don’t appear, copy the two `.code-snippets` files into your workspace’s `.vscode/` folder or import via “User Snippets”.

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

### Debugging helper (dout)

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

`debugger.cpp` knows how to print most STL containers, pairs, tuples, stacks, queues, and priority_queues.

### Included utilities in the templates

- Fast IO boilerplate, RNG: `mt19937_64 rng(...)` and `gen_random(l, r)`.
- `pbit(x)` to pretty-print bits of an integer.
- PBDS ordered multiset alias `oset` (from `<ext/pb_ds/...>`), plus a hash-table alias `ht`.
- Helpers: `smin(a,b)` and `smax(a,b)`.
- Macro `#define int long long` for quick 64-bit arithmetic.

Tips:
- If `#define int long long` gets in your way (interop with libraries/3rd-party code), replace it with a typedef like `using ll = long long;` and use `ll` explicitly.
- Keep `debugger.cpp` next to your solution file or adjust include paths accordingly.

That’s it—expand a snippet, code your solution, use `dout(...)` locally, and ship clean output to the judge.

## Common CP templates (copy-paste) 🚀

These are minimal, standalone snippets you can drop into any solution. They don’t depend on the debug helper.

### BFS on unweighted graph

```cpp
// 0-indexed adjacency list
vector<int> bfs(int n, const vector<vector<int>>& g, int src) {
	const int INF = 1e9;
	vector<int> dist(n, INF), par(n, -1);
	queue<int> q; q.push(src); dist[src] = 0;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int v : g[u]) if (dist[v] == INF) {
			dist[v] = dist[u] + 1; par[v] = u; q.push(v);
		}
	}
	return dist; // parents in par if you need the path
}
```

### DFS template (tin/tout, parent)

```cpp
void dfs(int u, int p, const vector<vector<int>>& g,
		 vector<int>& tin, vector<int>& tout, int& timer) {
	tin[u] = ++timer;
	for (int v : g[u]) if (v != p) dfs(v, u, g, tin, tout, timer);
	tout[u] = timer;
}
```

### Dijkstra (non-negative weights)

```cpp
// adj[u] = { {v, w}, ... }
vector<long long> dijkstra(int n, const vector<vector<pair<int,int>>>& adj, int s) {
	const long long INF = (1LL<<62);
	vector<long long> dist(n, INF); vector<int> par(n, -1);
	priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
	dist[s] = 0; pq.push({0, s});
	while (!pq.empty()) {
		auto [d, u] = pq.top(); pq.pop();
		if (d != dist[u]) continue;
		for (auto [v, w] : adj[u]) if (dist[v] > d + w) {
			dist[v] = d + w; par[v] = u; pq.push({dist[v], v});
		}
	}
	return dist; // parents in par if needed
}
```

### DSU (Union-Find) with union by size

```cpp
struct DSU {
	int n; vector<int> p, sz;
	DSU(int n=0): n(n), p(n), sz(n,1) { iota(p.begin(), p.end(), 0); }
	int find(int x){ return p[x]==x? x : p[x]=find(p[x]); }
	bool unite(int a, int b){ a=find(a); b=find(b); if(a==b) return false; if(sz[a]<sz[b]) swap(a,b); p[b]=a; sz[a]+=sz[b]; return true; }
	bool same(int a,int b){ return find(a)==find(b); }
};
```

### Segment Tree (range sum, point update)

```cpp
struct SegTree {
	int n; vector<long long> st;
	SegTree(int n=0){ init(n); }
	void init(int N){ n=1; while(n<N) n<<=1; st.assign(2*n,0); }
	void build(const vector<long long>& a){ init((int)a.size()); for(int i=0;i<(int)a.size();++i) st[n+i]=a[i]; for(int i=n-1;i>0;--i) st[i]=st[2*i]+st[2*i+1]; }
	void update(int idx, long long val){ int i=n+idx; st[i]=val; for(i>>=1;i;i>>=1) st[i]=st[2*i]+st[2*i+1]; }
	long long query(int l,int r){ // inclusive l,r
		long long L=0,R=0; for(l+=n,r+=n;l<=r;l>>=1,r>>=1){ if(l&1) L+=st[l++]; if(!(r&1)) R+=st[r--]; }
		return L+R;
	}
};
```

### Binary Search on Answer (first true)

```cpp
// Find smallest x in (lo, hi] such that pred(x) is true. pred must be monotonic.
template<class F>
long long first_true(long long lo, long long hi, F pred){
	while (hi - lo > 1) {
		long long mid = lo + (hi - lo)/2;
		if (pred(mid)) hi = mid; else lo = mid;
	}
	return hi; // caller ensures pred(hi) is true
}
```

### Modular arithmetic helpers (1e9+7)

```cpp
const long long MOD = 1'000'000'007LL;
long long addmod(long long a, long long b){ a+=b; if(a>=MOD) a-=MOD; return a; }
long long mulmod(long long a, long long b){ return (a%MOD) * (b%MOD) % MOD; }
long long binexp(long long a, long long e){ long long r=1%MOD; a%=MOD; while(e){ if(e&1) r=mulmod(r,a); a=mulmod(a,a); e>>=1; } return r; }
long long invmod(long long a){ return binexp(a, MOD-2); } // MOD must be prime

// nCr with O(1) queries after O(N) precompute
struct Comb {
	vector<long long> fact, invfact; long long M; int N;
	Comb(int n, long long M=MOD): M(M), N(n) {
		fact.resize(N+1); invfact.resize(N+1);
		fact[0]=1; for(int i=1;i<=N;i++) fact[i]=(fact[i-1]*i)%M;
		invfact[N]=binexp(fact[N], M-2); for(int i=N;i>0;i--) invfact[i-1]=(invfact[i]*i)%M;
	}
	long long nCr(int n, int r){ if(r<0||r>n) return 0; return (((fact[n]*invfact[r])%M)*invfact[n-r])%M; }
};
```

