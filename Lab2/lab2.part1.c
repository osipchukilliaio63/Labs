#include <stdio.h>

int main() {
    int n;
    printf("Write n: ");
    if (scanf("%d", &n) != 1) return 1;

    double x = 1.0 / 3.0;
    double S = 0.0;


    for (int i = 0; i <= n; i++) {
        double term = 1.0;


        for (int j = 0; j < 2 * i; j++) {
            term *= x;
        }


        if (i % 2 != 0) {
            term = -term;
        }

        S += term;
    }

    printf("Resault: %.7f\n", S);

    return 0;
}


