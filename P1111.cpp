#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
const int M = 100005;
int n, m, Father[N];
struct QUERY {
    int x, y, t;
} Queries[M];
int Find(int x) {
    if (Father[x] == x)
        return x;
    Father[x] = Find(Father[x]);
    return Father[x];
}
void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x > y)
        swap(x, y);
    if (x != y)
        Father[y] = x;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        Father[i] = i;
    for (int i = 0; i < m; i++)
        cin >> Queries[i].x >> Queries[i].y >> Queries[i].t;
    sort(Queries, Queries + m,
         [](QUERY a, QUERY b) -> bool {
             return a.t < b.t;
         });
    for (int i = 0; i < m; i++) {
        Union(Queries[i].x, Queries[i].y);
        bool Flag = true;
        for (int j = 2; j <= n; j++)
            if (Find(j) != 1) {
                Flag = false;
                break;
            }
        if (Flag) {
            cout << Queries[i].t << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    return 0;
}
