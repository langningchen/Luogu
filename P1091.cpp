#include <stdio.h>
int n, g[105], f[105], a[105], Answer;
#define getchar() (p1 == p2 && (p2 = (p1 = InputBuffer) + fread(InputBuffer, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)
char InputBuffer[1 << 20], *p1 = InputBuffer, *p2 = InputBuffer;
int Read() {
    int Number = 0;
    short Sign = 1;
    char c = ' ';
    while (c < '0' || c > '9') {
        c = getchar();
        if (c == '-') Sign = -1;
    }
    while (c >= '0' && c <= '9') {
        Number = Number * 10 + c - '0';
        c = getchar();
    }
    return Number * Sign;
}
void Write(int x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) Write(x / 10);
    putchar(x % 10 + '0');
}
int main() {
    n = Read();
    for (int i = 1; i <= n; i++)
        a[i] = Read();
    for (int i = 1; i <= n; i++)
        f[i] = g[i] = 1;
    for (int i = n - 1; i >= 1; i--)
        for (int j = i + 1; j <= n; j++)
            if (a[i] > a[j] && f[i] <= f[j] + 1)
                f[i] = f[j] + 1;
    for (int i = 2; i <= n; i++)
        for (int j = 1; j < i; j++)
            if (a[i] > a[j] && g[i] <= g[j] + 1)
                g[i] = g[j] + 1;
    for (int i = 1; i <= n; i++)
        if (f[i] + g[i] - 1 > Answer)
            Answer = f[i] + g[i] - 1;
    Write(n - Answer);
    return 0;
}