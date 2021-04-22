#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CardFunctions.h"

#define MAXCHAR 1000

void printBoard();
void showDeck();
element* C[7];
element* stack = NULL;

int main(){
    
    card* newCard = (card*)malloc(sizeof(card));

    for (size_t i = 0; i < 7; i++) //populate C[]
    {
        C[i] = (element*)(malloc(sizeof(element)));
    }
    
    top(stack);
    stack = (element*)(malloc(sizeof(element)));
    cardsFromFile(&stack);
    printBoard();
    showDeck();
}

void showDeck(){
    element* currentE = stack;
    for (size_t i = 0; i < 52; i++){ //kan antage at stack.length er 52 pga. input validering 
        
        *C[i % 7] = *currentE; 
        
        printf("%i : %s \n",i % 7, C[i % 7]->data.name);
        currentE = currentE->next;
    }
    
}
void printBoard(){
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n");
    for (size_t i = 0; i < 8; i++){
        for (size_t j = 0; j < 7; j++)
        {
            //printf(C[j]->data.name);
        }
        

    }
    
    
}