#include <bits/stdc++.h>
using namespace std;
int x, flag;
int main() {
    flag = false;
    cin >> x;
    if (x % 3 == 0) {
        cout << "3 ";
        flag = true;
    }
    if (x % 5 == 0) {
        cout << "5 ";
        flag = true;
    }
    if (x % 7 == 0) {
        cout << "7 ";
        flag = true;
    }
    if (!flag) cout << "n";
    cout << endl;
    return 0;
}