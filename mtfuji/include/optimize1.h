#pragma once
#include "func.h"

double calc_norm(double g[]);

int optimize(double a[], const double alpha, Sample* head, void (*calc_grad)(const double [], double [], Sample*), double (*f_value)(const double [], Sample*));