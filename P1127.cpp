#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
set<string> a[26];
string Answer;
int main() {
    cin >> n;
    for (ll i = 0; i < n; i++) {
        string s;
        cin >> s;
        a[s[0] - 'a'].insert(s);
    }
    string CurrentString = "";
    for (ll i = 0; i < 26; i++)
        if (a[i].size() != 0) {
            CurrentString = *a[i].begin();
            a[i].erase(a[i].begin());
            break;
        }
    Answer = CurrentString;
    ll Counter = 1;
    while (a[CurrentString[CurrentString.length() - 1] - 'a'].size()) {
        auto CurrentSet = &a[CurrentString[CurrentString.length() - 1] - 'a'];
        CurrentString = *CurrentSet->begin();
        CurrentSet->erase(CurrentSet->begin());
        Answer += "." + CurrentString;
        Counter++;
    }
    if (Counter != n)
        cout << "***" << endl;
    else
        cout << Answer << endl;
    return 0;
}