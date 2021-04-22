//
// Created by Emil Trangeled on 15-04-2021.
// Edit Nicolai B Kragh 

#include <stdio.h>
#include <stdlib.h>
#include "CardFunctions.h"
#include <string.h>
#include <mmcobj.h>

#define MAXCHAR 1000


 //element *head = NULL;
 element *current = NULL;

int valueFromCardName(char* name){
    switch (*name)
    {
    case 'A':
    case 'a':
        return 1;
    case 'J':
    case 'j':
        return 11;
    case 'Q':
    case 'q':
        return 12;
    case 'K':
    case 'k':
        return 13;
    default:
        if( 48<(int)*name<58 ){
            return (int)*name;
        }else{
            return -1; // error ! 
        };
        break;
    }
}

char suitFromCardName(char* name){
    return *(name+1);
}
void push(element* e, element** stack){
    //struct element* Element = (struct element*) malloc(sizeof (struct element));
    //Element ->data = data;
    e ->next = *stack;
    (*stack) = e;
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

void LoadCard(char* input, element** stack){
    //element* root = ( element*) malloc(sizeof ( element));
    //root ->data = *newCard;
    //root ->next = NULL;
    //printf("input: %s", input);
    card* newCard = (card *)malloc(sizeof(card));
    newCard->value = valueFromCardName(input);
    newCard->suit = suitFromCardName(input);

    strcpy(newCard->name, input); // kopier string ind i newCard->name
    //printf("newcard->name: %s \n", newCard->name);
    newCard->shown = 1;

    element* newElement = ( element*) malloc(sizeof ( element));
    newElement->data = *newCard;
    //printf("newcard->data.name: %s \n", newElement->data.name);
    newElement->next = NULL;
    //for (int i = 0; i < 10; ++i) {
        push(newElement, stack);
        top(*stack);
    //}
    free(newCard);
    newCard = NULL;
    free(newElement);
    newElement = NULL;
}

void cardsFromFile( element** stack){
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
        for (int j = 0; j < 12; ++j) {
            if (fgets(str, 4, fp) != NULL){
                //printf("from file: %s \t", str);
                str[strlen(str)-1] = '\0';
                LoadCard(str, stack);
            }
        }
        //printf("\n");
    }


//    while (fgets(str, MAXCHAR, fp) != NULL)
//        printf("%s\n", str);
    //shuffleList((element **) &stack);
    fclose(fp);


}
/* count how many elements there are in the list, then scan to the halfway point, breaking the last link */
//element* splitAtHalf (element* first){
//    size_t numElems = 52;
//    for (element* curr = first; curr != NULL ; curr = first->next) {
//        numElems++;
//    }
//
//    for (size_t i = 0; i < numElems / 2 - 1; ++i) {
//        first = first ->next;
//    }
//
//    element* result = (element *) first->next;
//    first ->next = NULL;
//    return result;
//
//}

//element* splitAtHalf (element* first){
//    element* fast = first;
//    while (fast ->next->next != NULL){
//        fast = fast ->next->next;
//        first = first ->next;
//    }
//
//    element* result = first ->next;
//    first->next = NULL;
//    return result;
//}
void splitList(struct element *head, struct element **head1_ref,
               struct element **head2_ref)
{
    struct element *slow_ptr = head;
    struct element *fast_ptr = head;

    if(head == NULL)
        return;

    /* If there are odd nodes in the circular list then
       fast_ptr->next becomes head and for even nodes
       fast_ptr->next->next becomes head */
    while(fast_ptr->next != head &&
          fast_ptr->next->next != head)
    {
        fast_ptr = fast_ptr->next->next;
        slow_ptr = slow_ptr->next;
    }

    /* If there are even elements in list then move fast_ptr */
    if(fast_ptr->next->next == head)
        fast_ptr = fast_ptr->next;

    /* Set the head pointer of first half */
    *head1_ref = head;

    /* Set the head pointer of second half */
    if(head->next != head)
        *head2_ref = slow_ptr->next;

    /* Make second half circular */
    fast_ptr->next = slow_ptr->next;

    /* Make first half circular */
    slow_ptr->next = head;
}


/* iteratively track the first element of one of the lists onto the back of the list being built, then to switch which list is which */
void interleave(element* first, element* second) {
    element* tail = NULL;
    /* Append the first element of 'second' to the list. */
    while (second != NULL){
        if (tail == NULL){
            tail = second;
        } else {
            tail ->next = second;
            tail = second;
        }
        /* cut the head of 'second' from 'second' */
        element* next = second ->next;
        second ->next = NULL;
        second = next;

        /* swap the two lists */
        element* temp = first;
        first = second;
        second = first;
    }
}
void printList(struct element *head){

    struct element *temp = head;
    while (temp != NULL){
        printf("%s\n", temp->data.name);
        temp = temp->next;
    }
}



/* first, split the list in half; second, shuffle the elements together. */
void shuffleList(element** head){
    if (* head == NULL) return;
    //struct element *head = NULL;
    struct element *head1 = NULL;
    struct element *head2 = NULL;

    splitList((struct element *) head, &head1, &head2);

//    struct element half = splitList((struct element *) head, &head1, &head2);
//    interleave(*head, half);
//    *head = half;


    printList((element *) head);
}

