#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1e6 + 5;
const ll INF = 0x3F3F'3F3F'3F3F'3F3F;

ll n, q, a[N];

namespace IO
{
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)
    char buf[1 << 20], *p1 = buf, *p2 = buf;
    template <typename T>
    T r()
    {
        T x = 0;
#ifndef LOCAL
        short s = 1;
        char c = ' ';
        while (c < '0' || c > '9')
            if ((c = getchar()) == '-')
                s = -1;
        while (c >= '0' && c <= '9')
            x = x * 10 + c - '0', c = getchar();
        return x * s;
#else
        cin >> x;
        return x;
#endif
    }
    template <typename T>
    void r(T &a) { a = r<T>(); }
    template <typename T, typename... U>
    inline void r(T &a, U &...args) { r(a), r(args...); }
    void w(char x) { putchar(x); }
    template <typename T, enable_if_t<is_convertible<T, string>::value, int> = 0>
    void w(T s)
    {
        for (char c : string(s))
            putchar(c);
    }
    template <typename T, enable_if_t<is_integral<T>::value, int> = 0>
    void w(T x)
    {
#ifndef LOCAL
        if (x < 0)
            putchar('-'), x = -x;
        if (x > 9)
            w(x / 10);
        putchar(x % 10 + '0');
#else
        cout << x;
#endif
    }
    template <typename T, typename... U>
    inline void w(T a, U... args) { w(a), w(args...); }
    void wl() { w('\n'); }
    template <typename T>
    void wl(T a) { w(a), wl(); }
    template <typename T, typename... U>
    inline void wl(T a, U... args) { w(a), wl(args...); }
} // namespace IO

#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid(l, r) (l + ((r - l) >> 1))
#define len(x) (ri[x] - le[x] + 1)
ll le[N << 2], ri[N << 2];
ll sgt[N << 2], lztAdd[N << 2], lztMod[N << 2];
void mtAdd(ll u, ll v) { sgt[u] += v, (lztMod[u] == INF ? lztAdd : lztMod)[u] += v; }
void mtMod(ll u, ll v) { sgt[u] = v, lztMod[u] = v, lztAdd[u] = 0; }
void pu(ll u) { sgt[u] = max(sgt[ls], sgt[rs]); }
void pd(ll u)
{
    if (lztMod[u] != INF)
        mtMod(ls, lztMod[u]), mtMod(rs, lztMod[u]), lztMod[u] = INF;
    else if (lztAdd[u])
        mtAdd(ls, lztAdd[u]), mtAdd(rs, lztAdd[u]), lztAdd[u] = 0;
}
void build(ll l = 1, ll r = n, ll u = 1)
{
    le[u] = l, ri[u] = r, lztAdd[u] = 0, lztMod[u] = INF;
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
        mtAdd(u, v);
    else
        pd(u), add(s, e, v, ls), add(s, e, v, rs), pu(u);
}
void mod(ll s, ll e, ll v, ll u = 1)
{
    if (e < le[u] || ri[u] < s)
        return;
    if (s <= le[u] && ri[u] <= e)
        mtMod(u, v);
    else
        pd(u), mod(s, e, v, ls), mod(s, e, v, rs), pu(u);
}
ll query(ll s, ll e, ll u = 1)
{
    if (e < le[u] || ri[u] < s)
        return -INF;
    if (s <= le[u] && ri[u] <= e)
        return sgt[u];
    pd(u);
    return max(query(s, e, ls), query(s, e, rs));
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
    IO::r(n, q);
    for (ll i = 1; i <= n; i++)
        IO::r(a[i]);
    build();
    while (q--)
    {
        ll op, l, r, x;
        IO::r(op, l, r);
        if (op == 1)
        {
            IO::r(x);
            mod(l, r, x);
        }
        else if (op == 2)
        {
            IO::r(x);
            add(l, r, x);
        }
        else
            IO::wl(query(l, r));
    }
    return 0;
}
