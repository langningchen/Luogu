#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 10007;
const ll N = 100005;
ll n, m, ans, a[N], b[N], s1[N][2], s2[N][2];
int main()
{
    ignore = freopen("P2671_2.in", "r", stdin);
    cin >> n >> m;
    for (ll i = 1; i <= n; i++)
        cin >> a[i];
    for (ll i = 1; i <= n; i++)
    {
        cin >> b[i];
        s1[b[i]][i % 2] = (s1[b[i]][i % 2] + 1) % MOD;
        s2[b[i]][i % 2] = (s2[b[i]][i % 2] + a[i]) % MOD;
    }
    for (ll i = 1; i <= n; i++)
    {
        // ans += i * ((s2[b[i]][i % 2] - a[i]) + a[i] * (s1[b[i]][i % 2] - 1)) % MOD;
        // ans %= MOD;
        ans = (ans + i * ((s1[b[i]][i % 2] - 1) * a[i] % MOD + (s2[b[i]][i % 2] - a[i]))) % MOD;
    }
    cout << ans << endl;
    return 0;
}
