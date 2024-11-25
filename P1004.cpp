#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 10;
ll n, ans, mp[N][N], f[N][N][N][N];
int main()
{
    cin >> n;
    int x, y, d;
    while (x != 0 || y != 0 || d != 0)
    {
        cin >> x >> y >> d;
        mp[x][y] = d;
    }
    f[1][1][1][1] = 1;
    for (int x1 = 1; x1 <= n; x1++)
        for (int y1 = 1; y1 <= n; y1++)
            for (int x2 = 1; x2 <= n; x2++)
                for (int y2 = 1; y2 <= n; y2++)
                    f[x1][y1][x2][y2] = max(max(f[x1 - 1][y1][x2 - 1][y2], f[x1 - 1][y1][x2][y2 - 1]),
                                            max(f[x1][y1 - 1][x2 - 1][y2], f[x1][y1 - 1][x2][y2 - 1])) +
                                        mp[x1][y1] + ((x1 == x2 && y1 == y2) ? 0 : mp[x2][y2]);
    cout << f[n][n][n][n] << endl;
    return 0;
}
