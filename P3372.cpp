#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
struct SEGMENT
{
    ll Left;
    ll Right;
    ll Length;
    ll Sum;
    ll LazyTag;
};
SEGMENT SegmentTree[N * 4];
int n, m, InitialValue[N];
void Build(ll NowPos, ll Left, ll Right)
{
    SegmentTree[NowPos].Left = Left;
    SegmentTree[NowPos].Right = Right;
    SegmentTree[NowPos].Length = Right - Left + 1;
    SegmentTree[NowPos].LazyTag = 0;
    if (Left == Right)
    {
        SegmentTree[NowPos].Sum = InitialValue[Left];
        return;
    }
    ll Middle = (Left + Right) / 2;
    Build(NowPos * 2, Left, Middle);
    Build(NowPos * 2 + 1, Middle + 1, Right);
    SegmentTree[NowPos].Sum = SegmentTree[NowPos * 2].Sum + SegmentTree[NowPos * 2 + 1].Sum;
}
void PushDown(ll NowPos)
{
    if (SegmentTree[NowPos].Left == SegmentTree[NowPos].Right)
        return;
    ll LazyTag = SegmentTree[NowPos].LazyTag;
    SegmentTree[NowPos].LazyTag = 0;
    SegmentTree[NowPos * 2].LazyTag += LazyTag;
    SegmentTree[NowPos * 2].Sum += SegmentTree[NowPos * 2].Length * LazyTag;
    SegmentTree[NowPos * 2 + 1].LazyTag += LazyTag;
    SegmentTree[NowPos * 2 + 1].Sum += SegmentTree[NowPos * 2 + 1].Length * LazyTag;
}
void Add(ll NowPos, ll Left, ll Right, ll Data)
{
    if (Right < SegmentTree[NowPos].Left || SegmentTree[NowPos].Right < Left)
        return;
    if (Left <= SegmentTree[NowPos].Left && SegmentTree[NowPos].Right <= Right)
    {
        SegmentTree[NowPos].LazyTag += Data;
        SegmentTree[NowPos].Sum += SegmentTree[NowPos].Length * Data;
        return;
    }
    PushDown(NowPos);
    Add(NowPos * 2, Left, Right, Data);
    Add(NowPos * 2 + 1, Left, Right, Data);
    SegmentTree[NowPos].Sum = SegmentTree[NowPos * 2].Sum + SegmentTree[NowPos * 2 + 1].Sum;
}
ll Query(ll NowPos, ll Left, ll Right)
{
    if (Right < SegmentTree[NowPos].Left || SegmentTree[NowPos].Right < Left)
        return 0;
    if (Left <= SegmentTree[NowPos].Left && SegmentTree[NowPos].Right <= Right)
        return SegmentTree[NowPos].Sum;
    PushDown(NowPos);
    return Query(NowPos * 2, Left, Right) + Query(NowPos * 2 + 1, Left, Right);
}
int main()
{
    cin >> n >> m;
    for (ll i = 1; i <= n; i++)
        cin >> InitialValue[i];
    Build(1, 1, n);
    for (ll i = 1; i <= m; i++)
    {
        ll t, l, r;
        cin >> t >> l >> r;
        if (t == 1)
        {
            int k;
            cin >> k;
            Add(1, l, r, k);
        }
        else
            cout << Query(1, l, r) << endl;
    }
    return 0;
}
