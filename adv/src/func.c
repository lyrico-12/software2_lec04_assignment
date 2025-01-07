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