#pragma once

typedef struct sample Sample;

char* trim_space(char* str);
void init_sample(Sample** head, char* filename);
Sample* push_back(Sample* head, char* loc, double alt, double temp);

void print_linear_list(Sample* head);

size_t sample_size();

void free_sample(Sample*);
void free_list(Sample*);


int f_dimension();

double predicted_temp(const double a[], double alt);

void f_gradient(const double a[], double g[], Sample* head);

double f_value(const double a[], Sample* head);

int comp_alt(const void*, const void*);
void sort_linear_list(Sample** head, int (*comp)(const void*, const void*));