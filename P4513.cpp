#include <bits/stdc++.h>
using namespace std;
typedef long ll;
const ll N = 5e5 + 5;
const ll INF = 0x3F3F'3F3F'3F3F'3F3F;

ll n, m, a[N];

#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid(l, r) (l + ((r - l) >> 1))
#define len(x) (ri[x] - le[x] + 1)
ll le[N << 2], ri[N << 2];
struct NODE
{
    ll sgt, maxV, maxL, maxR;
    void operator=(ll v) { sgt = maxV = maxL = maxR = v; }
} sgt[N << 2];
NODE operator+(const NODE &a, const NODE &b)
{
    return {a.sgt + b.sgt,
            max(max(max(a.maxR, b.maxL), a.maxR + b.maxL), max(a.maxV, b.maxV)),
            max(a.maxL, a.sgt + b.maxL),
            max(b.maxR, b.sgt + a.maxR)};
}
void pu(ll u) { sgt[u] = sgt[ls] + sgt[rs]; }
void build(ll l = 1, ll r = n, ll u = 1)
{
    le[u] = l, ri[u] = r;
    if (l == r)
    {
        sgt[u] = a[l];
        return;
    }
    ll m = mid(l, r);
    build(l, m, ls), build(m + 1, r, rs), pu(u);
}
void updateOne(ll x, ll v, ll u = 1)
{
    if (x < le[u] || ri[u] < x)
        return;
    if (le[u] == ri[u])
        sgt[u] = v;
    else
        updateOne(x, v, ls), updateOne(x, v, rs), pu(u);
}
NODE query(ll s, ll e, ll u = 1)
{
    if (le[u] >= s && ri[u] <= e)
        return sgt[u];
    ll m = mid(le[u], ri[u]);
    if (e <= m)
        return query(s, e, ls);
    if (s >= m + 1)
        return query(s, e, rs);
    return query(s, e, ls) + query(s, e, rs);
}
void print(ll u = 1)
{
    if (le[u] == ri[u])
        cerr << sgt[u].maxV << " \n"[le[u] == n];
    else
        print(ls), print(rs);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    for (ll i = 1; i <= n; i++)
        cin >> a[i];
    build();
    // print();
    for (ll i = 1, k, x, y; i <= m; i++)
    {
        cin >> k >> x >> y;
        if (k == 1)
        {
            if (x > y)
                swap(x, y);
            cout << query(x, y).maxV << endl;
        }
        else
            updateOne(x, y);
        // print();
    }
    return 0;
}
