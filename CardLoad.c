//
// Created by Emil Trangeled on 15-04-2021.
//

#include <stdio.h>
#include <stdlib.h>
#include "CardFunctions.h"

#define MAXCHAR 1000

struct element {
    char *data;
    int key;
    struct element* next;
};

struct element *head = NULL;
struct element *current = NULL;

void push(char *data, struct element** stack){
    struct element* Element = (struct element*) malloc(sizeof (struct element));
    Element ->data = data;
    Element ->next = *stack;
    (*stack) = Element;
}

void pop(struct element** stack){

    if (stack != NULL){
        printf("Element popped: %s\n", (*stack) -> data);
        struct element* tempPtr = *stack;
        *stack = (*stack) -> next;
        free(tempPtr);
    } else {
        printf("The Stack is empty.\n");
    }
}

void top(struct element* stack){
    if (stack != NULL){
        printf("Element on top: %s\n", stack -> data);
    } else {
        printf("The Stack is empty.\n");
    }
}

void LoadCards(void){
    struct element* root = (struct element*) malloc(sizeof (struct element));
    root ->data = "";
    root ->next = NULL;


    for (int i = 0; i < 10; ++i) {
        push("[]",&root);
        top(root);
    }
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