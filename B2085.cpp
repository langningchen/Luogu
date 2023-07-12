#include <bits/stdc++.h>
using namespace std;
const int N = 1000005;
bool IsNotPrime[N];
int n;
int main()
{
    cin >> n;
    IsNotPrime[0] = IsNotPrime[1] = true;
    for (int i = 2; i < N; i++)
        if (!IsNotPrime[i])
            for (int j = 2; i * j < N; j++)
                IsNotPrime[i * j] = true;
    for (int i = 2; i < N; i++)
    {
        if (!IsNotPrime[i])
            n--;
        if (n == 0)
        {
            cout << i << endl;
            break;
        }
    }
    return 0;
}
