#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CardFunctions.h"

#define MAXCHAR 1000



int main(){
    element* C[7];
    card* newCard = (card*)malloc(sizeof(card));

    element* stack = NULL;
    top(stack);
    stack = (element*)(malloc(sizeof(element)));
    cardsFromFile(&stack);
    shuffleList(&stack);

    // for(int i = 0; i < 7; i++){
    //     C[i] = malloc(sizeof(struct element));
    //     C[i]->next = (struct element*)malloc(sizeof(struct element));
    //     newCard->value = i;
    //     strcpy(newCard->name , "AA");
    //     newCard->shown = 0;
    //     C[i]->data = *newCard;
    // }
    // for(int i = 0; i < 7; i++){
    //     printf(" %d %s %d", (C[i]->data).value, (C[i]->data).name, (C[i]->data).shown);
    // }
    // FILE* inStream = fopen("Cards.txt","r"); 
    // char str[200];
    // if (!inStream) { printf( "Fejl i fil stream læsning");}
    // while(fgets(str, 200, inStream)) printf("%s", str);
    // fclose(inStream);
}