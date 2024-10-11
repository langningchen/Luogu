#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 3e4 + 5;

ll n;

ll cnt, head[N], nxt[N], to[N];
void ae(ll u, ll v) { nxt[++cnt] = head[u], to[cnt] = v, head[u] = cnt; }

ll fa[N], dep[N], sz[N], son[N];
void dfs1(ll u = 1) {
    sz[u] = 1;
    for (ll i = head[u]; i; i = nxt[i]) {
        ll v = to[i];
        if (v == fa[u]) continue;
        fa[v] = u, dep[v] = dep[u] + 1;
        dfs1(v);
        sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v;
    }
}

ll cnt2, top[N], dfn[N], rnk[N];
void dfs2(ll u = 1, ll t = 1) {
    top[u] = t, dfn[u] = ++cnt2, rnk[cnt2] = u;
    if (son[u]) dfs2(son[u], t);
    for (ll i = head[u]; i; i = nxt[i]) {
        ll v = to[i];
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

#define ls (u << 1)
#define rs (u << 1 | 1)
#define len(u) (ri[u] - le[u] + 1)
ll init[N << 2], sgt_s[N << 2], sgt_m[N << 2], tag[N << 2], le[N << 2], ri[N << 2];
void pu(ll u) { sgt_s[u] = sgt_s[ls] + sgt_s[rs]; }
void pd(ll u) {
    sgt_s[ls] += tag[u] * len(ls), sgt_m[ls] += tag[u], tag[ls] += tag[u];
    sgt_s[rs] += tag[u] * len(rs), sgt_m[ls] += tag[u], tag[ls] += tag[u];
    tag[u] = 0;
}
void build(ll u = 1, ll l = 1, ll r = n) {
    le[u] = l, ri[u] = r;
    if (l == r) return sgt_s[u] = init[rnk[l]], void();
    ll mid = l + (r - l >> 1);
    build(ls, l, mid), build(rs, mid + 1, r), pu(u);
}
void add(ll u, ll l, ll r, ll v) {
    if (le[u] >= l && ri[u] <= r) return sgt_s[u] += v * len(u), tag[u] += v, void();
    pd(u);
    ll mid = le[u] + ri[u] >> 1;
    if (l <= mid) add(ls, l, r, v);
    if (r > mid) add(rs, l, r, v);
    pu(u);
}

int main() {
    scanf("%lld", &n);
    for (ll i = 1; i < n; i++) {
        ll a, b;
        scanf("%lld%lld", &a, &b);
        ae(a, b), ae(b, a);
    }
    dfs1(), dfs2();
    return 0;
}