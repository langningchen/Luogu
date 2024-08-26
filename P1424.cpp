#include <bits/stdc++.h>
using namespace std;
int x, n, Answer;
int main() {
    cin >> x >> n;
    x = 8 - x;
    Answer = max(0, x - 2);
    Answer += (n - x) / 7 * 5;
    Answer += min((n - x) % 7, 5);
    cout << Answer * 250 << endl;
    return 0;
}