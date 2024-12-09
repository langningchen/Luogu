#include <bits/stdc++.h>
using namespace std;
const int N = 100005;

int n, m;

class SEGMENT_TREE
{
private:
    class SEGMENT
    {
    public:
        int Left, Right, Open, Close;
        bool LazyTag;
        SEGMENT() : Left(0), Right(0), Open(0), Close(0), LazyTag(false) {}
    } Segments[N * 4];

    inline int GetLeft(int x) { return (x << 1); }
    inline int GetRight(int x) { return (x << 1 | 1); }
    inline int GetMid(int x, int y) { return x + ((y - x) >> 1); }
    void PushDown(int ID)
    {
        if (Segments[ID].LazyTag)
        {
            swap(Segments[GetLeft(ID)].Open, Segments[GetLeft(ID)].Close);
            Segments[GetLeft(ID)].LazyTag = !Segments[GetLeft(ID)].LazyTag;
            swap(Segments[GetRight(ID)].Open, Segments[GetRight(ID)].Close);
            Segments[GetRight(ID)].LazyTag = !Segments[GetRight(ID)].LazyTag;
            Segments[ID].LazyTag = false;
        }
    }
    void Build(int ID, int Left, int Right)
    {
        Segments[ID].Left = Left;
        Segments[ID].Right = Right;
        Segments[ID].Close = Right - Left + 1;
        if (Left != Right)
        {
            int Mid = GetMid(Left, Right);
            Build(GetLeft(ID), Left, Mid);
            Build(GetRight(ID), Mid + 1, Right);
        }
    }
    void Modify(int ID, int Left, int Right)
    {
        if (Left > Segments[ID].Right || Right < Segments[ID].Left)
        {
            return;
        }
        if (Left <= Segments[ID].Left && Segments[ID].Right <= Right)
        {
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
    int Query(int ID, int Left, int Right)
    {
        if (Left > Segments[ID].Right || Right < Segments[ID].Left)
        {
            return 0;
        }
        if (Left <= Segments[ID].Left && Segments[ID].Right <= Right)
        {
            return Segments[ID].Open;
        }
        PushDown(ID);
        int Answer = 0;
        Answer += Query(GetLeft(ID), Left, Right);
        Answer += Query(GetRight(ID), Left, Right);
        return Answer;
    }

public:
    void Build(int NodeCount)
    {
        Build(1, 1, NodeCount);
    }
    void Modify(int Left, int Right)
    {
        Modify(1, Left, Right);
    }
    int Query(int Left, int Right)
    {
        return Query(1, Left, Right);
    }
};
SEGMENT_TREE SegmentTree;
int main()
{
    cin >> n >> m;
    SegmentTree.Build(n);
    for (int i = 1; i <= m; i++)
    {
        int c, a, b;
        cin >> c >> a >> b;
        if (c == 0)
            SegmentTree.Modify(a, b);
        else
            cout << SegmentTree.Query(a, b) << endl;
    }
    return 0;
}
