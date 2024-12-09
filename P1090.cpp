#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
priority_queue<int> q;
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        q.push(-x);
    }
    ll ans = 0;
    while (q.size() > 1)
    {
        int a = -q.top();
        q.pop();
        int b = -q.top();
        q.pop();
        ans += a + b;
        q.push(-(a + b));
    }
    cout << ans << endl;
    return 0;
}
