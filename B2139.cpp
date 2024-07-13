#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 100005;
ll m, n;
bool IsNotPrime[N];
int main() {
    for (ll i = 2; i < N; i++) {
        if (!IsNotPrime[i]) {
            for (ll j = 2 * i; j < N; j += i) {
                IsNotPrime[j] = true;
            }
        }
    }
    cin >> m >> n;
    vector<ll> Answer;
    for (int i = m; i <= n; i++) {
        auto Temp = to_string(i);
        reverse(Temp.begin(), Temp.end());
        if (!IsNotPrime[i] && !IsNotPrime[stoi(Temp)])
            Answer.push_back(i);
    }
    for (ll i = 0; i < Answer.size() - 1; i++)
        cout << Answer[i] << ",";
    cout << Answer[Answer.size() - 1] << endl;
    return 0;
}