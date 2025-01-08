#pragma once

// y = a0 * 1 + a1 * x1 + a2 * x2 + a3 * x3
// 標準化するのはx1, x2, x3, y (x0は全て１なので関係ない)
double calculate_mean(int len, double dataset[len][5], double means[4]);
double calculate_std(int len, double dataset[len][5], double stds[4]);

// datasetの値を書き換えて標準化する
void standerdization(int len, double dataset[len][5], double* y_mean, double* y_std);

// 目的変数の値を逆標準化する
void inverse_standerdization(int len, double predicted_y[len], const double y_mean, const double y_std);

// 目的変数の予測値
double predicted_y(const double a[4], const double data[5]);

// 目的変数の実測値と予測値を表示
void print_result(const double a[4], int len, const double dataset[len][5], double y_mean, double y_std, const double real_y[len]);