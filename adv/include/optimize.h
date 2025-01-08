#pragma once
#include "func.h"

double calc_norm(double g[4]);

int optimize(double a[4], double alpha, int len, double dataset[len][5], void (*calc_grad)(const double [], double [], int, const double dataset[len][5]),
             double (*f_value)(const double [], int, const double dataset[len][5]));