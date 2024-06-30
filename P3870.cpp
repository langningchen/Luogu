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
    } Segments[N * 4];
    ll NodeCount;
    inline ll GetLeft(ll x) { return (x << 1); }
    inline ll GetRight(ll x) { return (x << 1 | 1); }
    inline ll GetMid(ll x, ll y) { return x + ((y - x) >> 1); }
    void PushDown(ll ID) {
        if (Segments[ID].LazyTag) {
            swap(Segments[GetLeft(ID)].Open, Segments[GetLeft(ID)].Close);
            Segments[GetLeft(ID)].LazyTag = !Segments[GetLeft(ID)].LazyTag;
            swap(Segments[GetRight(ID)].Open, Segments[GetRight(ID)].Close);
            Segments[GetRight(ID)].LazyTag = !Segments[GetRight(ID)].LazyTag;
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
        if (Left <= Segments[ID].Left && Segments[ID].Right <= Right) {
            swap(Segments[ID].Open, Segments[ID].Close);
            Segments[ID].LazyTag = !Segments[ID].LazyTag;
        }
        if (Segments[ID].Right >= Left) Modify(GetLeft(ID), Left, Right);
        if (Right <= Segments[ID].Right) Modify(GetRight(ID), Left, Right);
    }
    ll Query(ll ID, ll Left, ll Right) {
        if (Left <= Segments[ID].Left && Segments[ID].Right <= Right) {
            return Segments[ID].Open;
        }
        PushDown(ID);
        ll Answer = 0;
        if (Segments[ID].Left <= Left) Answer += Query(GetLeft(ID), Left, Right);
        if (Right <= Segments[ID].Right) Answer += Query(GetRight(ID), Left, Right);
        return Answer;
    }

  public:
    void Build(ll NodeCount) {
        this->NodeCount = NodeCount;
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

/*
#include <bits/stdc++.h>
#define 空 void
#define 布尔 bool
#define 长整数 long long
#define 主函数 main
#define 交换 swap
#define 自己 this
#define 返回 return
#define 循环 for
#define 如果 if
#define 否则 else
#define 行内 inline
#define 常量 const
#define 输入 cin
#define 输出 cout
#define 换行 endl
#define 整数 int
#define 私有 private
#define 公共 public
#define 类 class
#define 的 .
#define 对应的 ->
#define 等于 ==
#define 不等于 !=
#define 自增 ++
#define 自减 --
#define 非 !
#define 加 +
#define 减 -
#define 乘 *
#define 除 /
#define 加上 +=
#define 减去 -=
#define 乘上 *=
#define 除去 /=
#define 左移 <<
#define 右移 >>
#define 输出有 <<
#define 输入有 >>
#define 与 &
#define 或 |
#define 赋值为 =
#define 小于 <
#define 大于 >
#define 小于等于 <=
#define 大于等于 >=
#define 并且 &&
#define 或者 ||
#define 那么 {
#define 就这样 }
#define 开始 {
#define 结束 }
#define 🆗 ;
using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

常量 长整数 最大 赋值为 1e5 加 5 🆗
长整数 灯数, 操作数 🆗
类 线段树类型 开始
    私有:
        类 线段类型 开始
            公共:
                长整数 左, 右, 开, 关 🆗
                布尔 懒标记 🆗
        结束 🆗
        线段类型 线段[最大 乘 4] 🆗
        长整数 节点数量 🆗
        行内 长整数 左子节点(长整数 编号) 开始 返回(编号 左移 1) 🆗 结束
        行内 长整数 右子节点(长整数 编号) 开始 返回(编号 左移 1 或 1) 🆗 结束
        行内 长整数 获得中间(长整数 一个, 长整数 另一个) 开始 返回 一个 加 ((另一个 减 一个) 右移 1) 🆗 结束
        空 下放(长整数 编号) 开始
            如果(线段[编号] 的 懒标记) 那么
                交换(线段[左子节点(编号)] 的 开, 线段[左子节点(编号)] 的 关) 🆗
                线段[左子节点(编号)] 的 懒标记 赋值为 非 线段[左子节点(编号)] 的 懒标记 🆗
                交换(线段[右子节点(编号)] 的 开, 线段[右子节点(编号)] 的 关) 🆗
                线段[右子节点(编号)] 的 懒标记 赋值为 非 线段[右子节点(编号)] 的 懒标记 🆗
            就这样
        结束
        空 建树(长整数 编号, 长整数 左, 长整数 右) 开始
            线段[编号] 的 左 赋值为 左 🆗
            线段[编号] 的 右 赋值为 右 🆗
            线段[编号] 的 关 赋值为 右 减 左 加 1 🆗
            如果(左 不等于 右) 那么
                长整数 中间 赋值为 获得中间(左, 右) 🆗
                建树(左子节点(编号), 左, 中间) 🆗
                建树(右子节点(编号), 中间 加 1, 右) 🆗
            就这样
        结束
        空 修改(长整数 编号, 长整数 左, 长整数 右) 开始
            如果(左 小于等于 线段[编号] 的 左 并且 线段[编号] 的 右 小于等于 右) 那么
                交换(线段[编号] 的 开, 线段[编号] 的 关) 🆗
                线段[编号] 的 懒标记 赋值为 非 线段[编号] 的 懒标记 🆗
            就这样
            如果(线段[左子节点(编号)] 的 右 大于等于 左)
            修改(左子节点(编号), 左, 右) 🆗
            如果(线段[右子节点(编号)] 的 左 小于等于 右)
            修改(右子节点(编号), 左, 右) 🆗
        结束
        长整数 查询(长整数 编号, 长整数 左, 长整数 右) 开始
            如果(左 小于等于 线段[编号] 的 左 并且 线段[编号] 的 右 小于等于 右) 那么
                返回 线段[编号] 的 开 🆗
            就这样
            下放(编号) 🆗
            长整数 答案 赋值为 0 🆗
            如果(线段[左子节点(编号)] 的 右 大于等于 左) 答案 加上 查询(左子节点(编号), 左, 右) 🆗
            如果(线段[右子节点(编号)] 的 左 小于等于 右) 答案 加上 查询(右子节点(编号), 左, 右) 🆗
            返回 答案 🆗
        结束

    公共:
        空 建树(长整数 节点数量) 开始
            自己 对应的 节点数量 赋值为 节点数量 🆗
            建树(1, 1, 节点数量) 🆗
        结束
        空 修改(长整数 左, 长整数 右) 开始
            修改(1, 左, 右) 🆗
        结束
        长整数 查询(长整数 左, 长整数 右) 开始
            返回 查询(1, 左, 右) 🆗
        结束
结束 🆗
线段树类型 线段树 🆗
整数 主函数() 开始
    输入 输入有 灯数 输入有 操作数 🆗
    线段树 的 建树(灯数) 🆗
    循环(长整数 循环变量 赋值为 1 🆗 循环变量 小于等于 操作数 🆗 循环变量 自增) 开始
        长整数 操作, 左边界, 右边界 🆗
        输入 输入有 操作 输入有 左边界 输入有 右边界 🆗
        如果(操作 等于 0) 线段树 的 修改(左边界, 右边界) 🆗
        否则 输出 输出有 线段树 的 查询(左边界, 右边界) 输出有 换行 🆗
    结束
    返回 0 🆗
结束
*/