#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "standerdization.h"

// y = a0 * 1 + a1 * x1 + a2 * x2 + a3 * x3
// 標準化するのはx1, x2, x3, y (x0は全て１なので関係ない)
void calculate_mean(int len, double dataset[len][5], double means[4]) {
    // dataset[_][0]は全て１だから飛ばす
    for (int i = 1; i < 5; i++) {
        double sum = 0.0;
        for (int j = 0; j < len; j++) {
            sum += dataset[j][i];
        }
        means[i - 1] = sum / (double)len;
    }
}

void calculate_std(int len, double dataset[len][5], double stds[4]) {
    double means[4];
    calculate_mean(len, dataset, means);
    // dataset[_][0]は全て１だから飛ばす
    for (int i = 1; i < 5; i++) {
        double s_2 = 0.0;
        for (int j = 0; j < len; j++) {
            s_2 += (dataset[j][i] - means[i - 1]) * (dataset[j][i] - means[i - 1]);
        }
        stds[i - 1] = sqrt(s_2 / (double)len);
    }
}

// datasetの値を書き換えて標準化する
void standerdization(int len, double dataset[len][5]) {
    double means[4];
    calculate_mean(len, dataset, means);
    double stds[4];
    calculate_std(len, dataset, stds);

    for (int i = 0; i < len; i++) {
        for (int j = 1; j < 5; j++) {
            dataset[i][j] = (dataset[i][j] - means[j - 1]) / stds[j - 1];
        }
    }
}