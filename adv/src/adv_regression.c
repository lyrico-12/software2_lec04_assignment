#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#include "optimize.h"

int main() {
    char filename[] = "src/AdsBud_and_Sales.csv";
    Data* head = NULL;

    // ファイルからデータ読み取り
    init_data(&head, filename);

    double train_p = 0.8;
    int train_len = (int)(train_p * list_len(head));
    int test_len = list_len(head) - train_len;
    double traindata[train_len][5];
    double testdata[test_len][5];
    // データを分割
    split_data(head, train_p, testdata, traindata);

    const double alpha = 0.01;

    // traindataの回帰分析
    double a1[4];
    for (int i = 0; i < 4; i++) {
        a1[i] = 1.0;
    }
    const int iter1 = optimize(a1, alpha, train_len, traindata, gradient, sse_value);
    double rss1 = calc_rss(a1, train_len, traindata);
    double tss1 = calc_tss(train_len, traindata);
    double r2_1 = calc_cod(rss1, tss1);

    // testdataの回帰分析
    double a2[4];
    for (int i = 0; i < 4; i++) {
        a2[i] = 1.0;
    }
    const int iter2 = optimize(a2, alpha, test_len, testdata, gradient, sse_value);
    double rss2 = calc_rss(a2, test_len, testdata);
    double tss2 = calc_tss(test_len, testdata);
    double r2_2 = calc_cod(rss2, tss2);

    printf("train data: number of iteration = %d, R^2 = %7.4f\n", iter1, r2_1);
    printf("test data: number of iteration = %d, R^2 = %7.4f\n", iter2, r2_2);

    free_data(head);

    return 0;
}