#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1e5 + 5;

ll n, m;

class SEGMENT_TREE {
  private:
    class SEGMENT {
      public:
        ll Left, Right, Open, Close;
        bool LazyTag;
        SEGMENT() : Left(0), Right(0), Open(0), Close(0), LazyTag(false) {}
    } Segments[N * 4];

    inline ll GetLeft(ll x) { return (x << 1); }
    inline ll GetRight(ll x) { return (x << 1 | 1); }
    inline ll GetMid(ll x, ll y) { return x + ((y - x) >> 1); }
    void PushDown(ll ID) {
        if (Segments[ID].LazyTag) {
            swap(Segments[GetLeft(ID)].Open, Segments[GetLeft(ID)].Close);
            Segments[GetLeft(ID)].LazyTag = !Segments[GetLeft(ID)].LazyTag;
            swap(Segments[GetRight(ID)].Open, Segments[GetRight(ID)].Close);
            Segments[GetRight(ID)].LazyTag = !Segments[GetRight(ID)].LazyTag;
            Segments[ID].LazyTag = false;
        }
    }
    void Build(ll ID, ll Left, ll Right) {
        Segments[ID].Left = Left;
        Segments[ID].Right = Right;
        Segments[ID].Close = Right - Left + 1;
        if (Left != Right) {
            ll Mid = GetMid(Left, Right);
            Build(GetLeft(ID), Left, Mid);
            Build(GetRight(ID), Mid + 1, Right);
        }
    }
    void Modify(ll ID, ll Left, ll Right) {
        if (Left > Segments[ID].Right || Right < Segments[ID].Left) {
            return;
        }
        if (Left <= Segments[ID].Left && Segments[ID].Right <= Right) {
            swap(Segments[ID].Open, Segments[ID].Close);
            Segments[ID].LazyTag = !Segments[ID].LazyTag;
            return;
        }
        PushDown(ID);
        Modify(GetLeft(ID), Left, Right);
        Modify(GetRight(ID), Left, Right);
        Segments[ID].Open = Segments[GetLeft(ID)].Open + Segments[GetRight(ID)].Open;
        Segments[ID].Close = Segments[GetLeft(ID)].Close + Segments[GetRight(ID)].Close;
    }
    ll Query(ll ID, ll Left, ll Right) {
        if (Left > Segments[ID].Right || Right < Segments[ID].Left) {
            return 0;
        }
        if (Left <= Segments[ID].Left && Segments[ID].Right <= Right) {
            return Segments[ID].Open;
        }
        PushDown(ID);
        ll Answer = 0;
        Answer += Query(GetLeft(ID), Left, Right);
        Answer += Query(GetRight(ID), Left, Right);
        return Answer;
    }

  public:
    void Build(ll NodeCount) {
        Build(1, 1, NodeCount);
    }
    void Modify(ll Left, ll Right) {
        Modify(1, Left, Right);
    }
    ll Query(ll Left, ll Right) {
        return Query(1, Left, Right);
    }
};
SEGMENT_TREE SegmentTree;
int main() {
    cin >> n >> m;
    SegmentTree.Build(n);
    for (int i = 1; i <= m; i++) {
        ll c, a, b;
        cin >> c >> a >> b;
        if (c == 0)
            SegmentTree.Modify(a, b);
        else
            cout << SegmentTree.Query(a, b) << endl;
    }
    return 0;
}
