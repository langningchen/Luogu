#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1e5 + 5;

int n, m, r, p, init[N];
vector<int> g[N];

int f[N], son[N], sz[N], dep[N];
void dfs1(int u, int fa) {
    sz[u] = 1;
    f[u] = fa;
    dep[u] = dep[fa] + 1;

    for (auto v : g[u]) {
        if (v == fa) continue;

        dfs1(v, u);
        sz[u] += sz[v];

        if (sz[v] > sz[son[u]])
            son[u] = v;
    }
}

int cnt2, top[N], dfn[N], rnk[N];
void dfs2(int u, int h) {
    top[u] = h, dfn[u] = ++cnt2, rnk[cnt2] = u;

    if (son[u] != 0) {
        dfs2(son[u], h);
        for (auto v : g[u]) {
            if (v != son[u] && v != f[u])
                dfs2(v, v);
        }
    }
}

#define ls (u << 1)
#define rs (u << 1 | 1)
ll sgt[N << 2], lzt[N << 2];
void pu(int u) { sgt[u] = (sgt[ls] + sgt[rs]) % p; }
void make_tag(int u, int len, ll x) {
    lzt[u] = (lzt[u] + x) % p;
    sgt[u] = (sgt[u] + len * x) % p;
}
void pd(int u, int l, int r) {
    int md = (l + r) >> 1;
    make_tag(ls, md - l + 1, lzt[u]);
    make_tag(rs, r - md, lzt[u]);
    lzt[u] = 0;
}
void build(int l = 1, int r = n, int u = 1) {
    if (l == r) {
        sgt[u] = init[rnk[l]];
        return;
    }
    int m = (l + r) >> 1;
    build(l, m, ls), build(m + 1, r, rs), pu(u);
}

void update(int u, int l, int r, int L, int R, ll x) {
    if (L <= l && r <= R)
        make_tag(u, r - l + 1, x);
    else if (!((l > R) || (r < L))) {
        int md = (l + r) >> 1;
        pd(u, l, r);
        update(ls, l, md, L, R, x);
        update(rs, md + 1, r, L, R, x);
        pu(u);
    }
}
ll query(int u, int l, int r, int L, int R) {
    if ((L <= l && r <= R))
        return sgt[u];
    else if (!((l > R) || (r < L))) {
        int md = (l + r) >> 1;
        pd(u, l, r);
        return (query(ls, l, md, L, R) + query(rs, md + 1, r, L, R)) % p;
    } else
        return 0;
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    cin >> n >> m >> r >> p;
    for (int i = 1; i <= n; i++)
        cin >> init[i];
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs1(r, 0);
    dfs2(r, 0);
    build(1, n, 1);
    for (int i = 0; i < m; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y, z;
            cin >> x >> y >> z;
            while (top[x] != top[y]) {
                if (dep[top[x]] < dep[top[y]]) swap(x, y);
                update(1, 1, n, dfn[top[x]], dfn[x], z);
                x = f[top[x]];
            }
            update(1, 1, n, min(dfn[x], dfn[y]), max(dfn[x], dfn[y]), z);

        } else if (op == 2) {
            int x, y;
            cin >> x >> y;
            ll ans = 0;
            while (top[x] != top[y]) {
                if (dep[top[x]] < dep[top[y]]) swap(x, y);
                ans = (ans + query(1, 1, n, dfn[top[x]], dfn[x])) % p;
                x = f[top[x]];
            }
            ans = (ans + query(1, 1, n, min(dfn[x], dfn[y]), max(dfn[x], dfn[y]))) % p;
            cout << ans << endl;
        } else if (op == 3) {
            int x, z;
            cin >> x >> z;
            update(1, 1, n, dfn[x], dfn[x] + sz[x] - 1, z);
        } else {
            int x;
            cin >> x;
            cout << query(1, 1, n, dfn[x], dfn[x] + sz[x] - 1) % p << endl;
        }
    }
    return 0;
}