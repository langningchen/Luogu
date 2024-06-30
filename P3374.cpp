#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template <typename T>
class BinaryIndexedTree {
  private:
    size_t n;
    T *Data;
    T LowBit(T x) { return x & (-x); }

  public:
    BinaryIndexedTree(size_t n) : n(n) {
        Data = new T[n + 1];
        fill(&Data[0], &Data[n + 1], 0);
    }
    ~BinaryIndexedTree() {
        delete[] Data;
    }
    void Add(size_t Position, T Value) {
        assert(0 < Position && Position <= n);
        for (size_t i = Position; i <= n; i += LowBit(i))
            Data[i] += Value;
    }
    T Query(size_t Position) {
        assert(Position <= n);
        T ans = 0;
        for (size_t i = Position; i > 0; i -= LowBit(i))
            ans += Data[i];
        return ans;
    }
    T Query(size_t Start, size_t End) {
        assert(0 < Start && Start <= n);
        assert(0 < End && End <= n);
        return Query(End) - Query(Start - 1);
    }
};
int main() {
    ll n, m;
    cin >> n >> m;
    BinaryIndexedTree<ll> BIT(n);
    for (ll i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        BIT.Add(i, x);
    }
    for (ll i = 1; i <= m; i++) {
        ll o;
        cin >> o;
        if (o == 1) {
            ll x, k;
            cin >> x >> k;
            BIT.Add(x, k);
        } else {
            ll x, y;
            cin >> x >> y;
            cout << BIT.Query(x, y) << endl;
        }
    }
    return 0;
}
