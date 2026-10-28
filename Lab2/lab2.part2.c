#include <stdio.h>

int main() {
    int n;
    printf("Write n: ");
    if (scanf("%d", &n) != 1) return 1;

    double x = 1.0 / 3.0;
    double S = 0.0;


    double term = 1.0;

    double multiplier = -(x * x);


    for (int i = 0; i <= n; i++) {
        S += term;
        term *= multiplier;
    }


    printf("Resault: %.7f\n", S);

    return 0;
}
