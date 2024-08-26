#include <stdbool.h>
#include <stdio.h>
int n, x, t, Flag[10000005];
long long Answer;
#define getchar() (p1 == p2 && (p2 = (p1 = InputBuffer) + fread(InputBuffer, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)
char InputBuffer[1 << 20], *p1 = InputBuffer, *p2 = InputBuffer;
int Read() {
    int Number = 0;
    char c = ' ';
    while (c < '0' || c > '9') {
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        Number = Number * 10 + c - '0';
        c = getchar();
    }
    return Number;
}
int main() {
    n = Read();
    for (int i = 0; i < n; i++) {
        x = Read(), t = Read();
        if (t > 1 && !Flag[x]) {
            Answer += t;
            Flag[x] = true;
        }
    }
    printf("%lld", Answer);
    return 0;
}