#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#include "optimize.h"
#include "standerdization.h"

int main() {
    char filename[] = "src/AdsBud_and_Sales.csv";
    Data* head = NULL;

    // ファイルからデータ読み取り
    init_data(&head, filename);

    double train_p = 0.8;
    int train_len = (int)(train_p * list_len(head));
    int test_len = list_len(head) - train_len;
    double traindata[train_len][5];
    double train_y[train_len];// 目的関数の実測値
    double testdata[test_len][5];
    double test_y[test_len];// 目的関数の実測値

    // データを分割
    split_data(head, train_p, testdata, traindata);

    for (int i = 0; i < train_len; i++) {
        train_y[i] = traindata[i][4];
    }

    for (int i = 0; i < test_len; i++) {
        test_y[i] = testdata[i][4];
    }

    double train_y_mean;
    double train_y_std;
    double test_y_mean;
    double test_y_std;

    // それぞれ標準化
    standerdization(train_len, traindata, &train_y_mean, &train_y_std);
    standerdization(test_len, testdata, &test_y_mean, &test_y_std);


    const double alpha = 0.01;

    // traindataの回帰分析
    printf("\n-----linear regression of traindata-----\n");
    double a1[4];
    for (int i = 0; i < 4; i++) {
        a1[i] = 1.0;
    }
    const int iter1 = optimize(a1, alpha, train_len, traindata, gradient, sse_value);
    double rss1 = calc_rss(a1, train_len, traindata);
    double tss1 = calc_tss(train_len, traindata);
    double r2_1 = calc_cod(rss1, tss1);// train datasetの決定係数

    // testdataの回帰分析
    printf("-----linear regression of testdata-----\n");
    double a2[4];
    for (int i = 0; i < 4; i++) {
        a2[i] = 1.0;
    }
    const int iter2 = optimize(a2, alpha, test_len, testdata, gradient, sse_value);
    double rss2 = calc_rss(a2, test_len, testdata);
    double tss2 = calc_tss(test_len, testdata);
    double r2_2 = calc_cod(rss2, tss2);// test datasetの決定係数

    // 分析の結果表示。目的変数の予測値と実測値、またその差の絶対値を表示
    printf("\n-------result of train data-------\n");
    print_result(a1, train_len, traindata, train_y_mean, train_y_std, train_y);
    printf("\n-------result of test data-------\n");
    print_result(a2, test_len, testdata, test_y_mean, test_y_std, test_y);

    // 重回帰分析モデルの評価。最適化時のイテレーション、決定係数を表示。
    printf("\n--------regression model validation-------\n");
    printf("train data: number of iteration = %d, R^2(決定係数) = %7.4f\n", iter1, r2_1);
    printf("test data: number of iteration = %d, R^2(決定係数) = %7.4f\n", iter2, r2_2);
    printf("---------------\n");

    free_data(head);

    return 0;
}