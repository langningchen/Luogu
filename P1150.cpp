#include <bits/stdc++.h>
using namespace std;
int n, k;
int main() {
    cin >> n >> k;
    cout << n + (n - 1) / (k - 1) << endl;
    return 0;
}