#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, s;
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        ll t;
        cin >> t;
        s += t;
    }
    cout << fixed << setprecision(2) << s * 1.0 / n << endl;
    return 0;
}