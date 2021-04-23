#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CardFunctions.h"


void printBoard(void);
void prepareShowStack(card* );
card* C[7];
card* stack = NULL;

int main(){
    for (size_t i = 0; i < 7; i++) //populate C[]
    {
        C[i] = (card*)(malloc(sizeof(card)));
        C[i]->next = NULL;
    }
    // element* newCard = (element*)malloc(sizeof(card));



    cardsFromFile(&stack);
    printBoard();   
    
    prepareShowStack(stack);
}

void prepareShowStack(card* s){

    
    card* currentE = s;
    for (size_t i = 0; i < 52; i++){ //kan antage at stack.length er 52 pga. input validering 
        card copyOfcurrentE = *currentE;
        //push(&copyOfcurrentE, (C[i % 7]) ); 
        printf("%i : %s \n",i % 7, C[i % 7]->name);
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