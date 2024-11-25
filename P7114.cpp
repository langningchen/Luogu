// 题目大意：给定一个字符串 $S$，求 $S = {(AB)}^iC$ 的方案数，其中 $F(A) \le F(C)$，$F(S)$ 表示字符串 $S$ 中出现奇数次的字符的数量。
// 知识点：字符串，倍增，哈希

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T;
template <typename T>
class BIT
{
private:
    vector<T> Tree;
    ll Lowbit(ll x)
    {
        return x & -x;
    }

public:
    BIT(ll n)
    {
        Tree.resize(n + 1);
    }
    void Update(ll x, T v)
    {
        while (x < Tree.size())
        {
            Tree[x] += v;
            x += Lowbit(x);
        }
    }
    T Query(ll x)
    {
        T res = 0;
        while (x > 0)
        {
            res += Tree[x];
            x -= Lowbit(x);
        }
        return res;
    }
};
vector<int> z_function(string s)
{
    int n = (int)s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i)
    {
        if (i <= r && z[i - l] < r - i + 1)
        {
            z[i] = z[i - l];
        }
        else
        {
            z[i] = max(0, r - i + 1);
            while (i + z[i] < n && s[z[i]] == s[i + z[i]])
                ++z[i];
        }
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

int main()
{
    // ignore = freopen("string.in", "r", stdin);
    // ignore = freopen("string.out", "w", stdout);
    cin >> T;
    while (T-- > 0)
    {
        string S;
        cin >> S;
        ll Answer = 0;
        ll n = S.size();
        vector<int> z = z_function(S);
        for (int i = 0; i < n; i++)
        {
            if (i + z[i] == n)
                z[i]--;
        }
        vector<int> before(26, 0), after(26, 0);
        vector<int> c(30, 0);
        ll pre = 0, suf = 0, all = 0;
        for (int i = 0; i < n; i++)
        {
            after[S[i] - 'a']++;
        }
        for (int i = 0; i < 26; i++)
            if (after[i] & 1)
                all++;
        suf = all;
        for (int i = 0; i < n; i++)
        {
            if (after[S[i] - 'a'] & 1)
                suf--;
            else
                suf++;
            after[S[i] - 'a']--;
            if (before[S[i] - 'a'] & 1)
                pre--;
            else
                pre++;
            before[S[i] - 'a']++;
            if (i != 0 && i != n - 1)
            {
                int t = z[i + 1] / (i + 1) + 1;
                Answer += 1LL * (t / 2) * c[all + 1] + 1LL * (t - t / 2) * c[suf + 1];
            }
            c[pre + 1]++;
        }
        cout << Answer << endl;
    }
    return 0;
}
