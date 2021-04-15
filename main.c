#include <stdio.h>
#include <stdlib.h>
#include "CardFunctions.h"

#define MAXCHAR 1000
struct Node {
    int data;
    struct Node* next;
};

int main(){
    struct Node* C[7];

    struct Node* head = NULL;
    struct Node* second = NULL;
    struct Node* third = NULL;
  
    // allocate 3 nodes in the heap
    for(int i = 0; i < 7; i++){
        C[i] = malloc(sizeof(struct Node));
        C[i]->next = (struct Node*)malloc(sizeof(struct Node));
        C[i]->data = 3;
        LoadCards();
    }
    for(int i = 0; i < 7; i++){
        printf(" %d",C[i]->data);
    }
    FILE* inStream = fopen("Cards.txt","r"); 
    char str[200];
    if (!inStream) { printf( "Fejl i fil stream læsning");}
    while(fgets(str, 200, inStream)) printf("%s", str);
    fclose(inStream);
}