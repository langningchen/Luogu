#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1e5 + 5;

ll n, m, a[N];

#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid(l, r) (l + ((r - l) >> 1))
#define len(x) (ri[x] - le[x] + 1)
ll le[N << 2], ri[N << 2];
ll sgt[N << 2], lzt[N << 2];
void mt(ll u, ll v) { sgt[u] += len(u) * v, lzt[u] += v; }
void pu(ll u) { sgt[u] = sgt[ls] + sgt[rs]; }
void pd(ll u)
{
    if (lzt[u])
        mt(ls, lzt[u]), mt(rs, lzt[u]), lzt[u] = 0;
}
void build(ll l = 1, ll r = n, ll u = 1)
{
    le[u] = l, ri[u] = r, lzt[u] = 0;
    if (l == r)
    {
        sgt[u] = a[l];
        return;
    }
    ll m = mid(l, r);
    build(l, m, ls), build(m + 1, r, rs), pu(u);
}
void add(ll s, ll e, ll v, ll u = 1)
{
    if (e < le[u] || ri[u] < s)
        return;
    if (s <= le[u] && ri[u] <= e)
        mt(u, v);
    else
        pd(u), add(s, e, v, ls), add(s, e, v, rs), pu(u);
}
ll query(ll s, ll e, ll u = 1)
{
    if (e < le[u] || ri[u] < s)
        return 0;
    if (s <= le[u] && ri[u] <= e)
        return sgt[u];
    pd(u);
    return query(s, e, ls) + query(s, e, rs);
}
void print(ll u = 1)
{
    if (le[u] == ri[u])
        cerr << sgt[u] << " \n"[le[u] == n];
    else
        pd(u), print(ls), print(rs);
}

int main()
{
    cin >> n >> m;
    for (ll i = 1, lst = 0, cur; i <= n; i++)
    {
        cin >> cur;
        a[i] = cur - lst;
        lst = cur;
    }
    build();
    // print();
    for (ll i = 1; i <= m; i++)
    {
        ll opt;
        cin >> opt;
        if (opt == 1)
        {
            ll l, r, k, d;
            cin >> l >> r >> k >> d;
            add(l, l, k);
            if (l + 1 <= r)
                add(l + 1, r, d);
            if (r + 1 <= n)
                add(r + 1, r + 1, -(k + d * (r - l)));
        }
        else
        {
            ll p;
            cin >> p;
            cout << query(1, p) << endl;
        }
        // print();
    }
    return 0;
}
