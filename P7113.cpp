// 题目大意：给定一个有向图，每个节点有若干个出度，每个节点有一个入度，求每个入度的节点的污水量

#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef __int128 lll;

// 分数
class FRACTION
{
private:
    lll Numerator, Denominator;
    void Simplify()
    {
        lll GCD = __gcd(Numerator, Denominator);
        Numerator /= GCD;
        Denominator /= GCD;
    }

public:
    FRACTION() : Numerator(0), Denominator(1) {}
    FRACTION(lll Numerator) : Numerator(Numerator), Denominator(1) {}
    FRACTION(lll Numerator, lll Denominator) : Numerator(Numerator), Denominator(Denominator)
    {
        Simplify();
    }
    FRACTION operator+(const FRACTION &x)
    {
        lll LCM = Denominator * x.Denominator / __gcd(Denominator, x.Denominator);
        lll NewNumerator = Numerator * (LCM / Denominator) + x.Numerator * (LCM / x.Denominator);
        return FRACTION(NewNumerator, LCM);
    }
    FRACTION operator/(const lll &x)
    {
        return FRACTION(Numerator, Denominator * x);
    }
    FRACTION &operator+=(const FRACTION &x)
    {
        *this = *this + x;
        return *this;
    }
    FRACTION &operator/=(const lll &x)
    {
        *this = *this / x;
        return *this;
    }
    auto GetNumerator()
    {
        Simplify();
        return Numerator;
    }
    auto GetDenominator()
    {
        Simplify();
        return Denominator;
    }
};

// 存图
template <typename T>
class GRAPH
{
private:
    int PointNumber, EdgeNumber;
    vector<int> *Edge;
    int *InDegree;
    int *OutDegree;
    T *Data;

public:
    GRAPH(int PointNumber) : PointNumber(PointNumber), EdgeNumber(0)
    {
        Edge = new vector<int>[PointNumber];
        InDegree = new int[PointNumber];
        OutDegree = new int[PointNumber];
        Data = new T[PointNumber];
        memset(InDegree, 0, sizeof(int) * PointNumber);
        memset(OutDegree, 0, sizeof(int) * PointNumber);
    }
    ~GRAPH()
    {
        delete[] Edge;
        delete[] InDegree;
        delete[] Data;
    }
    void AddEdge(int From, int To)
    {
        Edge[From].push_back(To);
        InDegree[To]++;
        OutDegree[From]++;
        EdgeNumber++;
    }
    void SetPointData(int Point, T Data)
    {
        this->Data[Point] = Data;
    }
    T GetPointData(int Point)
    {
        return Data[Point];
    }
    void DFS(int NowPos = 0, int LastPos = -1, T Delta = 1)
    {
        Delta /= LastPos == -1 ? 1 : Edge[LastPos].size();
        Data[NowPos] += Delta;
        for (int NextPos : Edge[NowPos])
            DFS(NextPos, NowPos, Delta);
    }
    auto GetInDegree(int Point)
    {
        return InDegree[Point];
    }
    auto GetOutDegree(int Point)
    {
        return OutDegree[Point];
    }
};

ostream &operator<<(ostream &OutputStream, lll Data)
{
    string StringData;
    while (Data)
    {
        StringData.push_back((char)(Data % 10 + '0'));
        Data /= 10;
    }
    for (int i = StringData.size() - 1; i >= 0; i--)
        OutputStream << StringData[i];
    return OutputStream;
}

int main()
{
    // ignore = freopen("P7113_10.in", "r", stdin);
    // ignore = freopen("P7713_10.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    GRAPH<FRACTION> G(n);
    for (int i = 0; i < n; i++)
    {
        int d;
        cin >> d;
        for (int j = 0; j < d; j++)
        {
            int a;
            cin >> a;
            G.AddEdge(i, a - 1);
        }
    }
    for (int i = 0; i < m; i++)
        G.DFS(i);
    for (int i = 0; i < n; i++)
        if (G.GetOutDegree(i) == 0)
            cout << G.GetPointData(i).GetNumerator() << " " << G.GetPointData(i).GetDenominator() << endl;
    return 0;
}
