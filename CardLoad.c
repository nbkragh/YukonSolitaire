//
// Created by Emil Trangeled on 15-04-2021.
//

#include <stdio.h>
#include "CardFunctions.h"

#define MAXCHAR 1000

void LoadCards(void){
    printf("Hej!\n");
}

void cardFromFile(void){
    FILE *fp;
    char str[MAXCHAR];
    char* filename = "..\\Cards.txt";

    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s\n", filename);

    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 12; ++j) {
            if (fgets(str, MAXCHAR, fp) != NULL){
                printf("%s \t", str);
            }

        }
        printf("\n");
    }


//    while (fgets(str, MAXCHAR, fp) != NULL)
//        printf("%s\n", str);
    fclose(fp);


}