#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 5e5 + 5;
ll n, a[N], b[N];
ll mergeSort(ll l = 1, ll r = n)
{
    if (l == r)
        return 0;
    ll m = l + ((r - l) >> 1);
    ll ans = mergeSort(l, m) + mergeSort(m + 1, r);
    ll i = l, j = m + 1, bi = 0;
    while (i <= m && j <= r)
        if (a[i] <= a[j])
            b[bi++] = a[i++];
        else
        {
            b[bi++] = a[j++];
            ans += m - i + 1;
        }
    while (i <= m)
        b[bi++] = a[i++];
    while (j <= r)
        b[bi++] = a[j++];
    for (ll i = l, j = 0; i <= r; i++, j++)
        a[i] = b[j];
    return ans;
}
int main()
{
    cin >> n;
    for (ll i = 1; i <= n; i++)
        cin >> a[i];
    cout << mergeSort() << endl;
    return 0;
}
