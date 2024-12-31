#pragma once

#include <stdlib.h>

typedef struct sample Sample;

char* trim_space(char* str);
void init_sample(Sample** head, char* filename);
Sample* push_back(Sample* head, char* loc, double alt, double temp);

void print_linear_list(Sample* head);

char* get_loc(Sample*);
double get_alt(Sample*);
double get_temp(Sample*);
size_t sample_size();

void free_sample(Sample*);


int f_dimension();

double predicted_temp(const double a[], double alt);

void f_gradient(const double a[], double g[], Sample* head);

double f_value(const double a[], Sample* head);