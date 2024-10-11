#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;

ll n, m, init[N];

#define ls (u << 1)
#define rs (u << 1 | 1)
#define len(x) (ri[x] - le[x] + 1)
ll le[N << 2], ri[N << 2];
ll sgt[N << 2], lzt[N << 2];
void pu(ll u) { sgt[u] = sgt[ls] + sgt[rs]; }
void pd(ll u) {
    sgt[ls] += len(ls) * lzt[u], lzt[ls] += lzt[u];
    sgt[rs] += len(rs) * lzt[u], lzt[rs] += lzt[u];
    lzt[u] = 0;
}
void build(ll l = 1, ll r = n, ll u = 1) {
    le[u] = l, ri[u] = r;
    if (l == r) {
        sgt[u] = init[l];
        return;
    }
    ll m = l + ((r - l) >> 1);
    build(l, m, ls), build(m + 1, r, rs), pu(u);
}
void add(ll s, ll e, ll v, ll u = 1) {
    if (e < le[u] || ri[u] < s) return;
    if (s <= le[u] && ri[u] <= e)
        sgt[u] += len(u) * v, lzt[u] += v;
    else
        pd(u), add(s, e, v, ls), add(s, e, v, rs), pu(u);
}
ll query(ll s, ll e, ll u = 1) {
    if (e < le[u] || ri[u] < s) return 0;
    if (s <= le[u] && ri[u] <= e) return sgt[u];
    pd(u);
    return query(s, e, ls) + query(s, e, rs);
}

int main() {
    cin >> n >> m;
    for (ll i = 1; i <= n; i++)
        cin >> init[i];
    build();
    for (ll i = 1; i <= m; i++) {
        ll t, l, r;
        cin >> t >> l >> r;
        if (t == 1) {
            int k;
            cin >> k;
            add(l, r, k);
        } else
            cout << query(l, r) << endl;
    }
    return 0;
}
