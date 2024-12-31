#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#include "optimize1.h"

int main() {
    char filename[] = "data.csv";
    Sample* head = NULL;

    init_sample(&head, filename);
    print_linear_list(head);

    const double alpha = 0.01;

    double a[2];
    a[0] = 1.0;
    a[1] = 20.0;

    const int iter = optimize(a, alpha, head, f_gradient, f_value);

    printf("number of iteration = %d\n", iter);

    printf("predicted Mt.fuji temperature = %f\n", predicted_temp(a, 3.776));

    free_list(head);
    return 0;
}