#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T, n, k;
int main() {
    cin >> T;
    while (T-- > 0) {
        cin >> n >> k;
        __uint128_t Answer = 0;
        for (ll i = 0; i < k; i++) {
            ll x;
            cin >> x;
            if (pow(2, i + 1) > n) break;
            Answer *= 2;
            if (x == 1) Answer++;
        }
    }
    return 0;
}
