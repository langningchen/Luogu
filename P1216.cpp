// #include <bits/stdc++.h>
// using namespace std;
// typedef long long ll;
// const int N = 1005;
// int n, a[N][N], f[N][N];
// int main()
// {
//     cin >> n;
//     for (int i = 1; i <= n; i++)
//         for (int j = 1; j <= i; j++)
//             cin >> a[i][j];
//     for (int i = 1; i <= n; i++)
//         for (int j = 1; j <= i; j++)
//             f[i][j] = max(f[i - 1][j], f[i - 1][j - 1]) + a[i][j];
//     cout << *max_element(f[n] + 1, f[n] + n + 1) << endl;
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
    int a[10] = {0};
    int *b = &a[5];
    cout << b[-1] << endl;
}
