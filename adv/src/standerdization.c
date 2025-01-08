#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "standerdization.h"

// y = a0 * 1 + a1 * x1 + a2 * x2 + a3 * x3
// 標準化するのはx1, x2, x3, y (x0は全て１なので関係ない)

// 便宜上、目的関数の平均と標準偏差は返り値にしておく。

double calculate_mean(int len, double dataset[len][5], double means[4]) {
    // dataset[_][0]は全て１だから飛ばす
    for (int i = 1; i < 5; i++) {
        double sum = 0.0;
        for (int j = 0; j < len; j++) {
            sum += dataset[j][i];
        }
        means[i - 1] = sum / (double)len;
    }
    return means[3];
}

double calculate_std(int len, double dataset[len][5], double stds[4]) {
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
    return stds[3];
}

// datasetの値を書き換えて標準化する
void standerdization(int len, double dataset[len][5], double* y_mean, double* y_std) {
    double means[4];
    *y_mean = calculate_mean(len, dataset, means);
    double stds[4];
    *y_std = calculate_std(len, dataset, stds);

    for (int i = 0; i < len; i++) {
        for (int j = 1; j < 5; j++) {
            dataset[i][j] = (dataset[i][j] - means[j - 1]) / stds[j - 1];
        }
    }
}

// 目的変数の値を逆標準化する
void inverse_standerdization(int len, double predicted_y[len], const double y_mean, const double y_std) {
    for (int i = 0; i < len; i++) {
        predicted_y[i] = predicted_y[i] * y_std + y_mean;
    }
}

// 目的変数の予測値
double predicted_y(const double a[4], const double data[5]) {
    double res = 0.0;
    for (int i = 0; i < 4; i++) {
        res += a[i] * data[i];
    }
    return res;
}

// 目的変数の実測値と予測値を表示
void print_result(const double a[4], int len, const double dataset[len][5], double y_mean, double y_std, const double real_y[len]) {
    double pre_y[len];
    for (int i = 0; i < len; i++) {
        pre_y[i] = predicted_y(a, dataset[i]);
    }

    inverse_standerdization(len, pre_y, y_mean, y_std);

    for (int i = 0; i < len; i++) {
        printf("%d predicted y: %7.4f, real y: %7.4f, abs of diff: %7.4f\n", i + 1, pre_y[i], real_y[i], fabs(pre_y[i] - real_y[i]));
    }
}