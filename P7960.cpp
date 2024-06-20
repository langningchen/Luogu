#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e7 + 100;
ll Index[N], LastAnswer, NextAnswer[N];
bool Has7(int x)
{
    while (x)
    {
        if (x % 10 == 7)
            return true;
        x /= 10;
    }
    return false;
}
int main()
{
    // freopen("P7960.in", "r", stdin);
    // freopen("P7960.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cout.tie(0);
    cin.tie(0);
    for (int i = 1; i <= N - 10; i++)
    {
        if (Index[i] == -1)
            continue;
        if (Has7(i))
            for (int j = i; j <= N - 10; j += i)
                Index[j] = -1;
        else
        {
            NextAnswer[LastAnswer] = i;
            LastAnswer = i;
        }
    }
    ll T;
    cin >> T;
    while (T-- > 0)
    {
        ll x;
        cin >> x;
        if (Index[x] == -1)
            cout << -1 << endl;
        else
            cout << NextAnswer[x] << endl;
    }
    return 0;
}
