#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 10007;
ll a, b, k, n, m;
int main()
{
    cin >> a >> b >> k >> n >> m;
    ll ans = 1;
    for (int i = 1; i <= n; i++)
        ans = ans * (a - i + 1) % MOD;
    for (int i = 1; i <= m; i++)
        ans = ans * (b - i + 1) % MOD;
    for (int i = 1; i <= k; i++)
        ans = ans * i % MOD;
    cout << ans << endl;
    return 0;
}
