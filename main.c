#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CardFunctions.h"


void printBoard(void);
void prepareShowStack(element* );
element* C[7];
element* stack = NULL;

int main(){
    
    card* newCard = (card*)malloc(sizeof(card));

    for (size_t i = 0; i < 7; i++) //populate C[]
    {
        C[i] = (element*)(malloc(sizeof(element)));
        C[i]->next = NULL;
    }

    cardsFromFile(stack);
    printBoard();   
    
    prepareShowStack(stack);
}

void prepareShowStack(element* s){

    
    element* currentE = s;
    for (size_t i = 0; i < 52; i++){ //kan antage at stack.length er 52 pga. input validering 
        element copyOfcurrentE = *currentE;
        push(&copyOfcurrentE, (C[i % 7]) ); 
        printf("%i : %s \n",i % 7, C[i % 7]->data.name);
        currentE = currentE->next;
    }
    free(currentE);
    currentE = NULL;
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