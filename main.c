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
    
    prepareShowStack(stack);
    printBoard();
}

void prepareShowStack(card* s){
    card* currentCard = s;
    for (size_t i = 0; i < 52; i++){ //kan antage at stack.length er 52 pga. input validering 
        
        push(&C[i % 7], createCard(currentCard->name));  //kopiér kort fra stack (createCard() ) og pladsér i C[i] listen
        currentCard = currentCard->next;
    }
    free(currentCard);
    currentCard = NULL;
}

/**
 * 
 */
void printBoard(){
    card* copyC[7];
    for (size_t i = 0; i < 7; i++)
    {
        copyC[i] = C[i];
    }
    
    printf("\nC1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");

    for (size_t i = 0; i < 52; i++){ //kan antage at stack.length er 52 pga. input validering 
        
        printf("%s\t", copyC[i % 7]->name);
        
        copyC[i % 7] = copyC[i % 7]->next;
        
        if((((i+1) % 7) == 0)){
            printf("\n");
        }
    }
    
    //free(copyC);
    //copyC == NULL;
}