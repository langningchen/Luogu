#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
const int K = 26;
int n, m;

// Trie
int fa[N], son[N][K], sonCnt[N], cnt, idx[N];
void add(string s, int i)
{
    int p = 0;
    for (size_t i = 0; i < s.size(); i++)
    {
        int u = s[i] - 'a';
        if (!son[p][u])
        {
            sonCnt[p]++;
            son[p][u] = ++cnt;
            fa[cnt] = p;
        }
        p = son[p][u];
    }
    idx[p] = i;
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        string t;
        cin >> t;
        add(t, i + 1);
    }
    string p;
    cin >> p;
    int cur = 0;
    string buff;
    for (int i = 0; i < m; i++)
    {
        if (p[i] == 'T')
        {
            if (buff.size() == 0)
                while (sonCnt[cur] == 1)
                    cur = son[cur][0];
        }
        else if (p[i] == 'B')
        {
            if (buff.size())
                buff.pop_back();
            else if (cur != 1)
                cur = fa[cur];
        }
        else if (p[i] == 'E')
        {
            if (!idx[cur] == 0 || buff.size())
                cout << -1 << " ";
            else
                cout << idx[cur] << " ";
            cur = 0;
            buff = "";
        }
        else
        {
            if (son[cur][p[i] - 'a'])
                cur = son[cur][p[i] - 'a'];
            else
                buff.push_back(p[i]);
        }
        cerr << cur << " " << buff << endl;
    }
    return 0;
}
