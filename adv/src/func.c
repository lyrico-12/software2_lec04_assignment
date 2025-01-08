#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

struct data {
    // 目的変数x[3]
    // x[0], x[1], x[2]
    // TV Ad Budget ($),Radio Ad Budget ($),Newspaper Ad Budget ($)
    double x[3];

    // 目的変数y
    // Sales ($)
    double y;
    struct data* next;
};

Data* push_back(Data* head, double x[3], double y) {
    if (head == NULL) {
        Data* p = (Data*)malloc(sizeof(Data));
        for (int i = 0; i < 3; i++) {
            p->x[i] = x[i];
        }
        p->y = y;
        p->next = NULL;
        return p;
    } else {
        Data* cur = head;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        Data* p = (Data*)malloc(sizeof(Data));
        for (int i = 0; i < 3; i++) {
            p->x[i] = x[i];
        }
        p->y = y;
        p->next = NULL;
        cur->next = p;
        return head;
    }
}

void print_linear_list(Data* head) {
    Data* cur = head;
    while(cur != NULL) {
        printf("x[0]: %f, x[1]: %f, x[2]: %f, y: %f\n", cur->x[0], cur->x[1], cur->x[2], cur->y);
        cur = cur->next;
    }
}

int list_len(Data* head) {
    int c = 0;
    Data* cur = head;
    while(cur != NULL) {
        c++;
        cur = cur->next;
    }
    return c;
}

void free_data(Data* head) {
    while (head != NULL) {
        Data* cur = head;
        head = head->next;
        free(cur);
    }
}

void init_data(Data** head, char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("ファイルを開けませんでした。\n");
    }
    char buf[128];
    double x[3];
    double y;
    while(fgets(buf, sizeof(buf), fp) != NULL) {
        if (buf[0] == ','){// 最初の行は飛ばす
            continue;
        } else {
            if (buf[strlen(buf) - 1] == '\n') {
                buf[strlen(buf) - 1] = '\0';
            }
            strtok(buf, ",");
            char* token;
            for (int i = 0; i < 3; i++) {
                token = strtok(NULL, ",");
                x[i] = (double)atof(token);
            }
            token = strtok(NULL, ",");
            y = (double)atof(token);
            *head = push_back(*head, x, y);
        }
    }
    fclose(fp);
}

// データを分割する関数。訓練データの割合をalphaとする
void split_data(Data* head, double alpha, double test[][5], double train[][5]){
    int len = list_len(head);
    int train_end_idx = (int) (alpha * len);

    Data* cur = head;
    int i = 0;
    while (cur != NULL) {
        if (i < train_end_idx) {
            train[i][0] = 1.0;
            for (int j = 1; j < 4; j++) {
                train[i][j] = cur->x[j - 1];
            }
            train[i][4] = cur->y;
        } else {
            test[i - train_end_idx][0] = 1.0;
            for (int j = 1; j < 4; j++) {
                test[i - train_end_idx][j] = cur->x[j - 1];
            }
            test[i - train_end_idx][4] = cur->y;
        }
        i++;
        cur = cur->next;
    }
}

// 損失関数はSum of Square Errorsを用いる
// predict_y = a[0] * x0 + a[1] * x1 + a[2] * x2 + a[3] * x3 (x0 = 1)
double sse_value(const double a[4], int len, const double dataset[len][5]) {
    double res = 0.0;
    for (int i = 0; i < len; i++) {
        double predict_y = 0.0;
        for (int j = 0; j < 4; j++) {
            predict_y += a[j] * dataset[i][j];
        }
        res += (dataset[i][4] - predict_y) * (dataset[i][4] - predict_y);
    }
    return (1.0 / 2.0 * len) * res;
}

// sse_valueの勾配ベクトルの計算
void gradient(const double a[4], double g[4], int len, const double dataset[len][5]) {
    for (int i = 0; i < 4; i++) {
        g[i] = 0.0;
    }

    for (int j = 0; j < 4; j++) {
        for (int k = 0; k < len; k++) {
            double predict_y = 0.0;
            for (int i = 0; i < 4; i++) {
                predict_y += a[i] * dataset[k][i];
            }
            g[j] += (dataset[k][4] - predict_y) * dataset[k][j];
        }
        g[j] *= -1.0 / (double)len;
    }
}

double calc_mean(int len, const double dataset[len][5]) {
    double sum = 0.0;
    for (int i = 0; i < len; i++) {
        sum += dataset[i][4];
    }
    return sum / (double)len;
}

// 残差平方和(RSS)
double calc_rss(const double a[], int len, const double dataset[len][5]) {
    double rss = 0.0;
    for (int i = 0; i < len; i++) {
        double predict_y = 0.0;
        for (int j = 0; j < 4; j++) {
            predict_y += a[j] * dataset[i][j];
        }
        rss += (dataset[i][4] - predict_y) * (dataset[i][4] - predict_y);
    }
    return rss;
}

// 総平方和(TSS)
double calc_tss(int len, const double dataset[len][5]) {
    double mean = calc_mean(len, dataset);

    double tss = 0.0;
    for (int i = 0; i < len; i++) {
        tss += (dataset[i][4] - mean) * (dataset[i][4] - mean);
    }
    return tss;
}

// 決定係数を求める
double calc_cod(double rss, double tss) {
    return 1.0 - (rss / tss);
}