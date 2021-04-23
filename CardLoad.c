//
// Created by Emil Trangeled on 15-04-2021.
// Edit Nicolai B Kragh 

#include <stdio.h>
#include <stdlib.h>
#include "CardFunctions.h"
#include <string.h>
#include <ctype.h>
//#include <ctype.h>
#define MAXCHAR 1000


 element *head = NULL;
 element *current = NULL;

int valueFromCardName(char* name){
    switch (toupper(*name))
    {
    case 'A':
        return 1;
    case 'T':
        return 10;
    case 'J':
        return 11;
    case 'Q':
        return 12;
    case 'K':
        return 13;
    default:
        if( 48<(int)*name<58 ){
            return ((int)*name)-48;
        }else{
            return -1; // error ! 
        };
        break;
    }
}

char suitFromCardName(char* name){
    return *(name+1);
}
void push(element* e, element* stack){
    //struct element* Element = (struct element*) malloc(sizeof (struct element));
    //Element ->data = data;
    e ->next = stack;
    (stack) = e;
    top(stack);
}

void pop( element** stack){

    if (stack != NULL){
        printf("Element popped: %s\n", (*stack) -> data);
         element* tempPtr = *stack;
        *stack = (*stack) -> next;
        free(tempPtr);
    } else {
        printf("The Stack is empty.\n");
    }
}

void top( element* stack){
    if (stack != NULL){
        printf("Element on top: %s\n", stack -> data.name);
    } else {
        printf("The Stack is empty.\n");
    }
}

void LoadCard(char* input, element* stack){
    //element* root = ( element*) malloc(sizeof ( element));
    //root ->data = *newCard;
    //root ->next = NULL;
    card* newCard = (card *)malloc(sizeof(card));
    newCard->value = valueFromCardName(input);
    newCard->suit = suitFromCardName(input);
    strcpy(newCard->name, input); // kopier string ind i newCard->name
    newCard->shown = 1;

    element* newElement = ( element*) malloc(sizeof ( element));
    newElement->data = *newCard;
    newElement->next = NULL;
    push(newElement, stack);
    //top(*stack);

    free(newCard);
    newCard = NULL;
}

void cardsFromFile( element* stack){
    FILE *fp;
    char str[4];
    char* filename = "..\\Cards.txt";

    fp = fopen(filename, "r");
    if (fp == NULL){
        filename = "Cards.txt"; // prøv at kigge efter filen i samme mappe stedet for
        fp = fopen(filename, "r");
        if (fp == NULL){
            printf("Could not open file %s\n", filename);
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 13; ++j) {
            if (fgets(str, 4, fp) != NULL){
                str[strlen(str)-1] = '\0';
                LoadCard(str, stack);
            }
        }
    }

    fclose(fp);


}
