#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
set<string> a[26];
string ans;
int main()
{
    cin >> n;
    for (ll i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        a[s[0] - 'a'].insert(s);
    }
    for (ll i = 0; i < 26; i++)
        if (a[i].size() != 0)
        {
            ans = *a[i].begin();
            a[i].erase(a[i].begin());
            break;
        }
    auto s = &a[ans[ans.length() - 1] - 'a'];
    while (s->size())
    {
        ans += "." + *s->begin();
        s->erase(s->begin());
        s = &a[ans[ans.length() - 1] - 'a'];
    }
    if (ans == "")
        cout << "***" << endl;
    else
        cout << ans << endl;
    return 0;
}
