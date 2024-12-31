#include "optimize1.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double calc_norm(double g[]) {
    double tmp = g[0] * g[0] + g[1] * g[1];
    return sqrt(tmp);
}

int optimize(double a[], const double alpha, Sample* head, void (*calc_grad)(const double [], double [], Sample*), double (*f_value)(const double [], Sample*)) {
    // gradient
    double g[2];

    
    int ite = 0;// 繰り返し
    while (++ite < 10000) {
        (*calc_grad)(a, g, head);

        const double e = f_value(a, head);
        const double norm = calc_norm(g);

        printf("%3d norm = %7.4f, a = %7.4f, b = %7.4f, E = %f\n", ite, norm, a[0], a[1], e);
        if (norm < 0.001) {
            break;
        }

        a[0] -= alpha * g[0];
        a[1] -= alpha * g[1];
    }

    return ite;
}