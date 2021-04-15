#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CardFunctions.h"

#define MAXCHAR 1000

struct Card {
    int  value;
    char name[2];
    int shown;
};
struct Node {
    struct Card data;
    struct Node* next;
};

int main(){
    struct Node* C[7];
    struct Card* newCard = malloc(sizeof(struct Card));
    
    // allocate 3 nodes in the heap
    for(int i = 0; i < 7; i++){
        C[i] = malloc(sizeof(struct Node));
        C[i]->next = (struct Node*)malloc(sizeof(struct Node));
        newCard->value = i;
        strcpy(newCard->name , "AA");
        newCard->shown = 0;
        C[i]->data = *newCard;
    }
    for(int i = 0; i < 7; i++){
        printf(" %d %s %d", (C[i]->data).value, (C[i]->data).name, (C[i]->data).shown);
    }
    FILE* inStream = fopen("Cards.txt","r"); 
    char str[200];
    if (!inStream) { printf( "Fejl i fil stream læsning");}
    while(fgets(str, 200, inStream)) printf("%s", str);
    fclose(inStream);
}