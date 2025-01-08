#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "optimize.h"

double calc_norm(double g[4]) {
    double norm = 0.0;

    for (int i = 0; i < 4; i++) {
        norm += g[i] * g[i];
    }
    return sqrt(norm);
}


// aは回帰係数ベクトル、alphaは最急降下法のパラメータ、datasetには訓練データまたはテストデータが入る。calc_gradにはベクトルを
int optimize(double a[4], double alpha, int len, double dataset[len][5], void (*calc_grad)(const double [], double [], int, const double dataset[len][5]),
             double (*f_value)(const double [], int, const double dataset[len][5])) {
    double g[4];

    int iter = 0;

    while (++iter < 1000) {
        // 勾配ベクトル計算
        (*calc_grad)(a, g, len, dataset);

        const double norm = calc_norm(g);

        // 繰り返し回数が10の倍数だったら表示する
        if (iter % 10 == 0) {
            printf("%3d norm = %7.4f", iter, norm);
            for (int i = 0; i < 4; i++) {
                printf(", a[%d] = %7.4f", i, a[i]);
            }
            const double sse = f_value(a, len, dataset);
            printf(", sse = %f\n", sse);
        }

        if (norm < 0.001) {
            break;
        }

        // 最急降下法
        for (int i = 0; i < 4; i++) {
            a[i] -= alpha * g[i];
        }

    }
    return iter;
}