#include <bits/stdc++.h>
using namespace std;
int n, m;
int sqn; // 每个块的大小
int c, a, b;
int nm;            // 块的数量
bool bulb[100010]; // 单灯泡是否亮
bool tag[1010];    // 区间反转
int dis[100010];   // 灯泡对应的块的 ID
int bulbnum[1010]; // 每个块的灯泡数量
int litnum[1010];  // 点亮等的灯泡数量
int lf[1010];      // 块的左边界
int rt[1010];      // 块的右边界
void add()
{
    if (lf[dis[a]] != a)
    {
        for (int i = a; i <= rt[dis[a]]; i++)
        {
            if (bulb[i] == true)
                litnum[dis[i]]--;
            else
                litnum[dis[i]]++;
            bulb[i] = !bulb[i];
        }
        a = lf[dis[a] + 1];
    }
    for (int i = dis[a]; rt[i] <= b && i <= nm; i++)
        tag[i] = !tag[i];
    if (rt[dis[b]] != b)
    {
        for (int i = lf[dis[b]]; i <= b; i++)
        {
            if (bulb[i] == true)
                litnum[dis[i]]--;
            else
                litnum[dis[i]]++;
            bulb[i] = !bulb[i];
        }
    }
}
void find()
{
    int ans = 0;
    if (lf[dis[a]] != a)
    {
        for (int i = a; i <= rt[dis[a]]; i++)
        {
            if (bulb[i] == true && tag[dis[i]] == false)
                ans++;
            else if (bulb[i] == false && tag[dis[i]] == true)
                ans++;
        }
        a = lf[dis[a] + 1];
    }
    for (int i = dis[a]; rt[i] <= b && i <= nm; i++)
    {
        if (tag[i])
            ans += bulbnum[i] - litnum[i];
        else
            ans += litnum[i];
    }
    if (rt[dis[b]] != b)
    {
        for (int i = lf[dis[b]]; i <= b; i++)
        {
            if (bulb[i] == true && tag[dis[i]] == false)
                ans++;
            else if (bulb[i] == false && tag[dis[i]] == true)
                ans++;
        }
    }
    cout << ans << endl;
}
int main()
{
    cin >> n >> m;
    sqn = sqrt(n);
    for (int i = 1; i <= n; i++)
    {
        dis[i] = (i - 1) / sqn;
        bulbnum[dis[i]]++;
        nm = max(nm, dis[i]);
    }
    for (int i = 1; i <= n; i++)
        if (dis[i - 1] < dis[i])
        {
            rt[dis[i - 1]] = i - 1;
            lf[dis[i]] = i;
        }
    lf[0] = 1;
    rt[nm] = n;
    for (int i = 1; i <= m; i++)
    {
        cin >> c >> a >> b;
        if (c == 0)
            add();
        else
            find();
    }
}
