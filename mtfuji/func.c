#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

struct sample {
    char* loc;
    double alt;
    double temp;
    struct sample* next;
};

char* trim_space(char* str) {
    while (*str == ' '){
        str++;
    }
    return str;
}


Sample* push_back(Sample* head, char* loc, double alt, double temp){
    if (head == NULL) {
        Sample* p = (Sample*)malloc(sizeof(Sample));
        char* s = (char*)malloc(strlen(loc) + 1);
        strcpy(s, loc);
        *p = (Sample) {.loc = s, .alt = alt, .temp = temp, .next = NULL};
        return p;
    } else {
        Sample* cur = head;
        while(cur->next != NULL) {
            cur = cur->next;
        }
        Sample* p = (Sample*)malloc(sizeof(Sample));
        char* s = (char*)malloc(sizeof(strlen(loc) + 1));
        strcpy(s, loc);
        *p = (Sample) {.loc = s, .alt = alt, .temp = temp, .next = NULL};
        cur->next = p;
        return head;
    }
}

void init_sample(Sample** head, char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("ファイルを開けませんでした\n");
    }
    char buf[128];
    char* loc;
    double alt, temp;
    while ((fgets(buf, sizeof(buf) ,fp)) != NULL) {
        if (buf[strlen(buf) - 1] == '\n') {
            buf[strlen(buf) - 1] = '\0';
        }
        loc = strtok(buf, ",");
        char* token;
        token = strtok(NULL, ",");
        alt = (double)atof(trim_space(token));
        token = strtok(NULL, ",");
        temp= (double)atof(trim_space(token));
        *head = push_back(*head, loc, alt, temp);
    }
    fclose(fp);
}

void print_linear_list(Sample* head) {
    Sample* cur = head;
    while(cur != NULL) {
        printf("loc: %s, alt: %f, temp: %f\n", cur->loc, cur->alt, cur->temp);
        cur = cur->next;
    }
}

size_t sample_size() {
    return sizeof(Sample);
}

void free_sample(Sample* s) {
    free(s->loc);
    free(s);
}

void free_list(Sample* head) {
    Sample* cur = head;
    while (cur != NULL) {
        Sample* next = cur->next;
        free_sample(cur);
        cur = next;
    }
}

double predicted_temp(const double a[], double alt) {
    return a[0] * alt + a[1];
}

void f_gradient(const double a[], double g[], Sample* head) {
    Sample* cur = head;
    double g0 = 0.0;
    double g1 = 0.0;

    while (cur != NULL) {
        g0 += -2.0 * cur->alt * (cur->temp - a[0] * cur->alt - a[1]);
        g[0] = g0;
        g1 += -2.0 * (cur->temp - a[0] * cur->alt - a[1]);
        g[1] = g1;

        cur = cur->next;
    }
}

double f_value(const double a[], Sample* head) {
    double res = 0.0;
    Sample* cur = head;
    while(cur != NULL) {
        res += (cur->temp - a[0] * cur->alt - a[1]) * (cur->temp - a[0] * cur->alt - a[1]);
        cur = cur->next;
    }
    return res;
}