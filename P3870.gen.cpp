#include <bits/stdc++.h>
using namespace std;
int n = 1e5, m = 1e2;
int main()
{
    srand(time(nullptr));
    cout << n << " " << m << endl;
    for (int i = 0; i < m; i++)
    {
        int x = rand() % n;
        int y = rand() % n;
        if (x > y)
            swap(x, y);
        cout << rand() % 2 << " " << x << " " << y << endl;
    }
    return 0;
}
