#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;

int n, q, m, a[N];

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

class mint
{
    ll v;

public:
    mint() : v(0) {}
    mint(ll v) : v((v + m) % m) {}
    operator ll() const { return v; }

    mint operator+(const mint &o) const
    {
        ll tmp = v + o.v;
        if (tmp >= m)
            tmp -= m;
        return tmp;
    }
    mint operator-(const mint &o) const
    {
        ll tmp = v + m - o.v;
        if (tmp >= m)
            tmp -= m;
        return tmp;
    }
    mint operator*(const mint &o) const { return v * o.v % m; }
    mint operator/(const mint &o) const { return *this * o.inv(); }

    mint &operator+=(const mint &o) { return *this = *this + o; }
    mint &operator-=(const mint &o) { return *this = *this - o; }
    mint &operator*=(const mint &o) { return *this = *this * o; }
    mint &operator/=(const mint &o) { return *this = *this / o; }

    bool operator==(const mint &o) const { return v == o.v; }
    bool operator!=(const mint &o) const { return v != o.v; }
    bool operator<(const mint &o) const { return v < o.v; }
    bool operator>(const mint &o) const { return v > o.v; }
    bool operator<=(const mint &o) const { return v <= o.v; }
    bool operator>=(const mint &o) const { return v >= o.v; }

    mint pow(ll exp) const
    {
        mint base = *this;
        mint result = 1;
        while (exp > 0)
        {
            if (exp % 2 == 1)
                result *= base;
            base *= base;
            exp /= 2;
        }
        return result;
    }
    mint inv() const { return pow(m - 2); }

    friend std::istream &operator>>(std::istream &in, mint &a)
    {
        ll tmp;
        in >> tmp;
        a = mint(tmp);
        return in;
    }
    friend std::ostream &operator<<(std::ostream &out, const mint &a)
    {
        out << a.v;
        return out;
    }
};

mint sgt[N << 2], lztAdd[N << 2], lztMul[N << 2];
ll le[N << 2], ri[N << 2];
#define ls (u << 1)
#define rs (u << 1 | 1)
#define len(u) (ri[u] - le[u] + 1)
#define mid(x, y) (x + ((y - x) >> 1))
void pdMul(ll u);
void pdAdd(ll u);
void mtAdd(ll u, ll v) { sgt[u] += v * len(u), lztAdd[u] = lztAdd[u] + mint(v); }
void mtMul(ll u, ll v) { sgt[u] *= v, lztAdd[u] *= v, lztMul[u] *= v; }
void pu(ll u) { sgt[u] = sgt[ls] + sgt[rs]; }
void pdAdd(ll u) { mtAdd(ls, lztAdd[u]), mtAdd(rs, lztAdd[u]), lztAdd[u] = 0; }
void pdMul(ll u) { mtMul(ls, lztMul[u]), mtMul(rs, lztMul[u]), lztMul[u] = 1; }
void pd(ll u) { pdMul(u), pdAdd(u); }
void build(ll l = 1, ll r = n, ll u = 1)
{
    le[u] = l, ri[u] = r, lztAdd[u] = 0, lztMul[u] = 1;
    if (l == r)
    {
        sgt[u] = a[l];
        return;
    }
    ll m = mid(l, r);
    build(l, m, ls), build(m + 1, r, rs), pu(u);
}
void add(ll s, ll e, ll d, ll u = 1)
{
    if (s <= le[u] && ri[u] <= e)
        mtAdd(u, d);
    else if (ri[u] < s || e < le[u])
        return;
    else
        pd(u), add(s, e, d, ls), add(s, e, d, rs), pu(u);
}
void mul(ll s, ll e, ll d, ll u = 1)
{
    if (s <= le[u] && ri[u] <= e)
        mtMul(u, d);
    else if (ri[u] < s || e < le[u])
        return;
    else
        pd(u), mul(s, e, d, ls), mul(s, e, d, rs), pu(u);
}
mint query(ll s, ll e, ll u = 1)
{
    if (s <= le[u] && ri[u] <= e)
        return sgt[u];
    else if (ri[u] < s || e < le[u])
        return 0;
    else
        return pd(u), query(s, e, ls) + query(s, e, rs);
}
void print(ll u = 1)
{
    if (le[u] == ri[u])
        cerr << sgt[u] << " \n"[le[u] == n];
    else
        pd(u), print(ls), print(rs);
}
void debug(ll u = 1, ll dep = 0)
{
    for (ll i = 0; i < dep; i++)
        cerr << "  ";
    cerr << le[u] << "~" << ri[u] << ": " << sgt[u] << "  (" << lztAdd[u] << ", " << lztMul[u] << ")" << endl;
    if (le[u] != ri[u])
        debug(ls, dep + 1), debug(rs, dep + 1);
}

int main()
{
    IO::r(n, q, m);
    for (ll i = 1; i <= n; i++)
        IO::r(a[i]);
    build();
    // debug();
    // print();
    for (ll i = 0, op, x, y; i < q; i++)
    {
        IO::r(op, x, y);
        if (op == 1)
            mul(x, y, IO::r<ll>());
        else if (op == 2)
            add(x, y, IO::r<ll>());
        else
            IO::wl(ll(query(x, y)));
        // print();
    }
    return 0;
}
