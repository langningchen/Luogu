#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 105;
ll n, g[N], f[N], a[N], Answer;
int main() {
    cin >> n;
    for (ll i = 1; i <= n; i++)
        cin >> a[i];
    fill(f + 1, f + n + 1, 1);
    fill(g + 1, g + n + 1, 1);
    for (ll i = n - 1; i >= 1; i--)
        for (ll j = i + 1; j <= n; j++)
            if (a[i] > a[j] && f[i] <= f[j] + 1)
                f[i] = f[j] + 1;
    for (ll i = 2; i <= n; i++)
        for (ll j = 1; j < i; j++)
            if (a[i] > a[j] && g[i] <= g[j] + 1)
                g[i] = g[j] + 1;
    for (ll i = 1; i <= n; i++)
        Answer = max(Answer, f[i] + g[i] - 1);
    cout << n - Answer << endl;
    return 0;
}