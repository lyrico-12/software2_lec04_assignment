#pragma once

// y = a0 * 1 + a1 * x1 + a2 * x2 + a3 * x3
// 標準化するのはx1, x2, x3, y (x0は全て１なので関係ない)
void calculate_mean(int len, double dataset[len][5], double means[4]);
void calculate_std(int len, double dataset[len][5], double stds[4]);

// datasetの値を書き換えて標準化する
void standerdization(int len, double dataset[len][5]);