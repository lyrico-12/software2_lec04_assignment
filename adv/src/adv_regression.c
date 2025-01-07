#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

int main() {
    char filename[] = "src/AdsBud_and_Sales.csv";
    Data* head = NULL;

    init_data(&head, filename);
    print_linear_list(head);
    return 0;
}