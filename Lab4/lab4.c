#include <stdio.h>

int main() {
    int m, n;
    double A[10][10];
    int i, j;

    printf("Enter m and n (7..10): ");
    scanf("%d %d", &m, &n);

    if (m < 1 || m > 10 || n < 1 || n > 10) {
        printf("Wrong size!\n");
        return 1;
    }

    printf("Enter matrix elements:\n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }

    printf("\nMatrix:\n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("%7.2lf ", A[i][j]);
        }
        printf("\n");
    }

    int found = 0;
    int res_i = -1, res_j = -1;
    int L, R, mid;

    for (i = 0; i < m; i++) {
        L = 0;
        R = n - 1;

        while (L < R) {
            mid = (L + R) / 2;
            if (A[i][mid] > 5.0) {
                L = mid + 1;
            } else {
                R = mid;
            }
        }

        if (A[i][L] >= 0.0 && A[i][L] <= 5.0) {
            found = 1;
            res_i = i;
            res_j = L;
            break;
        }
    }

    if (found) {
        printf("\nFound: %.2lf at [%d][%d]\n", A[res_i][res_j], res_i, res_j);
    } else {
        printf("\nNot found\n");
    }

    return 0;
}

