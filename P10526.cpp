#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
const int K = 26;
int n, m;

int fa[N], son[N][K], sonCnt[N], oneSon[N], cnt, idx[N], tab[N];
void add(string s, int i)
{
    int p = 0;
    for (size_t i = 0; i < s.size(); i++)
    {
        int u = s[i] - 'a';
        if (!son[p][u])
        {
            sonCnt[p]++;
            oneSon[p] = u;
            son[p][u] = ++cnt;
            fa[cnt] = p;
        }
        p = son[p][u];
    }
    idx[p] = i;
}
int getTab(int x)
{
    if (sonCnt[x] != 1 || idx[x] != 0)
        return x;
    if (tab[x] != -1)
        return tab[x];
    return tab[x] = getTab(son[x][oneSon[x]]);
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        string t;
        cin >> t;
        add(t, i);
    }
    fill(tab, tab + N, -1);
    string p;
    cin >> p;
    int cur = 0, more = 0;
    for (int i = 0; i < m; i++)
    {
        if (p[i] == 'T')
        {
            if (!more)
                cur = getTab(cur);
        }
        else if (p[i] == 'B')
        {
            if (more)
                more--;
            else if (cur != 0)
                cur = fa[cur];
        }
        else if (p[i] == 'E')
        {
            if (!idx[cur] || more)
                cout << -1 << " ";
            else
                cout << idx[cur] << " ";
            cur = more = 0;
        }
        else
        {
            if (son[cur][p[i] - 'a'])
                cur = son[cur][p[i] - 'a'];
            else
                more++;
        }
        // cerr << cur << " \"" << buff << "\"" << endl;
    }
    return 0;
}
