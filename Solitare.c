//
// Created by Emil Trangeled on 15-04-2021.
//

#include <stdio.h>
#include <stdlib.h>
#include "CardFunctions.h"

int main(void){

    LoadCards();

    for (int i = 1; i <= 7; ++i ){
        printf("C%d \t",i);
    }
    printf("\n");

    for (int i = 0; i <= 7; ++i) {
        for (int j = 1; j <= 7; ++j) {
            printf("KC\t");
        }
        printf("\n");
    }
    return 0;
}



