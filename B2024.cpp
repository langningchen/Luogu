#include <stdio.h>
double d;
int main() {
    scanf("%lf", &d);
    printf("%f\n%0.5f\n%e\n%g\n", d, d, d, d);
    return 0;
}