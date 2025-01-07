#pragma once

typedef struct data Data;

Data* push_back(Data* head, double x[3], double y);
void print_linear_list(Data* head);
int list_len(Data* head);

void init_data(Data** head, char* filename);