#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1e5 + 5;
ll n, m, r, p, init[N], x, y, z, op;
ll cnt, head[N], nxt[N << 1], to[N << 1];

ll fa[N], son[N], sz[N], dep[N];
void dfs1(ll u) {
    sz[u] = 1;
    for (ll i = head[u]; i; i = nxt[i]) {
        ll v = to[i];
        if (v == fa[u]) continue;
        dep[v] = dep[u] + 1, fa[v] = u;
        dfs1(v);
        sz[u] += sz[v];
        if (!son[u] || sz[v] > sz[son[u]]) son[u] = v;
    }
}

ll cnt2, top[N], dfn[N], rnk[N];
void dfs2(ll u, ll h) {
    top[u] = h, dfn[u] = ++cnt2, rnk[cnt2] = u;
    if (!son[u]) {
        return;
    }
    dfs2(son[u], h);
    for (ll i = head[u]; i; i = nxt[i]) {
        ll v = to[i];
        if (v != son[u] && v != fa[u]) dfs2(v, v);
    }
}

#define ls (u << 1)
#define rs (u << 1 | 1)
#define len(x) (ri[x] - le[x] + 1)
ll le[N << 2], ri[N << 2];
ll sgt[N << 2], lzt[N << 2];
void pu(ll u) { sgt[u] = (sgt[ls] + sgt[rs]) % p; }
void pd(ll u) {
    sgt[ls] = (sgt[ls] + len(ls) % p * lzt[u]) % p, lzt[ls] = (lzt[ls] + lzt[u]) % p;
    sgt[rs] = (sgt[rs] + len(rs) % p * lzt[u]) % p, lzt[rs] = (lzt[rs] + lzt[u]) % p;
    lzt[u] = 0;
}
void build(ll l = 1, ll r = n, ll u = 1) {
    le[u] = l, ri[u] = r;
    if (l == r) {
        sgt[u] = init[rnk[l]] % p;
        return;
    }
    ll m = l + ((r - l) >> 1);
    build(l, m, ls), build(m + 1, r, rs), pu(u);
}
void add(ll s, ll e, ll v, ll u = 1) {
    if (e < le[u] || ri[u] < s) return;
    if (s <= le[u] && ri[u] <= e)
        sgt[u] = (sgt[u] + len(u) % p * v) % p, lzt[u] = (lzt[u] + v) % p;
    else
        pd(u), add(s, e, v, ls), add(s, e, v, rs), pu(u);
}
ll query(ll s, ll e, ll u = 1) {
    if (e < le[u] || ri[u] < s) return 0;
    if (s <= le[u] && ri[u] <= e) return sgt[u];
    pd(u);
    return (query(s, e, ls) + query(s, e, rs)) % p;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> m >> r >> p;
    for (ll i = 1; i <= n; i++)
        cin >> init[i];
    for (ll i = 1; i < n; i++) {
        cin >> x >> y;
        nxt[++cnt] = head[x], to[cnt] = y, head[x] = cnt;
        nxt[++cnt] = head[y], to[cnt] = x, head[y] = cnt;
    }
    dfs1(r);
    // for (ll i = 1; i <= n; i++)
    dfs2(r, r);
    // for (ll i = 1; i <= n; i++)
    //     cerr << dfn[top[i]] << " " << bottom[i] << endl;
    // return 0;
    build();
    for (ll i = 0; i < m; i++) {
        cin >> op;
        if (op == 1) {
            cin >> x >> y >> z;
            z %= p;
            while (top[x] != top[y]) {
                if (dep[top[x]] < dep[top[y]]) swap(x, y);
                // cerr << dfn[x] << "~" << dfn[top[x]] << " +" << z << endl;
                add(dfn[top[x]], dfn[x], z);
                x = fa[top[x]];
            }
            // cerr << dfn[x] << "~" << dfn[y] << " +" << z << endl;
            add(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]), z);
        } else if (op == 2) {
            cin >> x >> y;
            ll ans = 0;
            while (top[x] != top[y]) {
                if (dep[top[x]] < dep[top[y]]) swap(x, y);
                // cerr << dfn[x] << "~" << dfn[top[x]] << "?" << endl;
                ans = (ans + query(dfn[top[x]], dfn[x])) % p;
                x = fa[top[x]];
            }
            // cerr << dfn[x] << "~" << dfn[y] << "?" << endl;
            ans = (ans + query(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]))) % p;
            cout << ans << endl;
        } else if (op == 3) {
            cin >> x >> z;
            z %= p;
            // cerr << dfn[x] << "~" << bottom[x] << " +" << z << endl;
            add(dfn[x], dfn[x] + sz[x] - 1, z);
        } else {
            cin >> x;
            // cerr << dfn[x] << "~" << bottom[x] << "?" << endl;
            cout << query(dfn[x], dfn[x] + sz[x] - 1) << endl;
        }
    }
    return 0;
}