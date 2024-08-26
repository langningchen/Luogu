#include <bits/stdc++.h>
using namespace std;
string s, a, b;
int main() {
    getline(cin, s);
    getline(cin, a);
    getline(cin, b);
    size_t Pos;
    while ((Pos = s.find(a)) != string::npos) {
        s = s.replace(Pos, Pos + a.length(), b);
    }
    cout << s << endl;
    return 0;
}