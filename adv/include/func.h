#pragma once

typedef struct data Data;

// 線形リストに関する関数
Data* push_back(Data* head, double x[3], double y);
void print_linear_list(Data* head);
int list_len(Data* head);
void free_data(Data* head);

// csvファイルを線形リストに格納する関数
void init_data(Data** head, char* filename);

// データを分割する関数。訓練データの割合をalphaとする
void split_data(Data* head, double alpha, double test[][5], double train[][5]);

// 損失関数はSum of Square Errorsを用いる
double sse_value(const double a[4], int len, const double dataset[len][5]);

// sse_valueの勾配ベクトル
void gradient(const double a[4], double g[4], int len, const double dataset[len][5]);

// 目的変数の予測値
double predicted_y(const double a[4], const double data[5]);

// 決定係数を求めるための関数たち
double calc_mean(int len, const double dataset[len][5]);
double calc_rss(const double a[], int len, const double dataset[len][5]);
double calc_tss(int len, const double dataset[len][5]);
double calc_cod(double rss, double tss);
