//
// Created by Emil Trangeled on 15-04-2021.
// Edit Nicolai B Kragh 

#include <stdio.h>
#include <stdlib.h>
#include "CardFunctions.h"
#include <string.h>
#include <ctype.h>
#include <mmcobj.h>

//#define MAXCHAR 1000


 //card *head = NULL;
 //card *current = NULL;

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
card* createCard(char* input){ // create nyt kort fra string
    
    struct card *ptr1 = (card *)malloc(sizeof(card));
    ptr1->value = valueFromCardName(input);
    ptr1->suit = suitFromCardName(input);
    strcpy(ptr1->name, input);
    ptr1->shown = 1;
    return ptr1;
}

void push(card **start, card* inCard){
    if (*start == NULL){
        inCard->next = inCard->prev = inCard;
        *start = inCard;
        return;
    }
    card *last = (*start) ->prev;

    inCard->next = *start;
    (*start)->prev = inCard;
    inCard->prev = last;
    last->next = inCard;
}



//void push2(struct card **head_ref, char* input){
//    struct card *ptr1 = (struct card *)malloc(sizeof(struct card));
//    struct card *temp = *head_ref;
//    ptr1->value = valueFromCardName(input);
//    ptr1->suit = suitFromCardName(input);
//    strcpy(ptr1->name, input);
//    ptr1->shown = 1;
//    ptr1->next = *head_ref;
//
//    /* If linked list is not NULL then set the next of
//      last node */
//    if(*head_ref != NULL)
//    {
//        while(temp->next != *head_ref)
//            temp = temp->next;
//        temp->next = ptr1;
//    }
//    else
//        ptr1->next = ptr1; /*For the first node */
//
//    *head_ref = ptr1;
//}
int countNodes(struct card* head)
{
    struct card* temp = head;
    int result = 0;
    if (head != NULL) {
        do {
            temp = temp->next;
            result++;
        } while (temp != head);
    }

    return result;
}

/* Function to print nodes in a given Circular linked list */
void printList(struct card *head){

    //struct card *temp = head;
    for (int i = 0; i < countNodes(head); ++i) {
        printf("%s ", head->name);
        //printf("\n");
        head = head->next;
    }

}

void pop(card** stack){

    if (stack != NULL){
        printf("Element popped: %s\n", (*stack) ->name);
        card* tempPtr = *stack;
        *stack = (*stack) -> next;
        free(tempPtr);
    } else {
        printf("The Stack is empty.\n");
    }
}

void top(card* stack){
    if (stack != NULL){
        printf("Element on top: %s\n", stack ->name);
    } else {
        printf("The Stack is empty.\n");
    }
}
void splitList(struct card *head, struct card **head1_ref, struct card **head2_ref) {
    struct card *slow_ptr = head;
    struct card *fast_ptr = head;

    if(head == NULL)
        return;

    /* If there are odd nodes in the circular list then
       fast_ptr->next becomes head and for even nodes
       fast_ptr->next->next becomes head */
    while(fast_ptr->next != head && fast_ptr->next->next != head) {
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

void LoadCard(char* input, card** stack){
    //card* root = ( card*) malloc(sizeof ( card));
    //root ->data = *newCard;
    //root ->next = NULL;
    //printf("input: %s", input);
    //card* newCard = (card *)malloc(sizeof(card));
    //newCard->value = valueFromCardName(input);
    //newCard->suit = suitFromCardName(input);

    //strcpy(newCard->name, input); // kopier string ind i newCard->name
    //printf("newcard->name: %s \n", newCard->name);
    //newCard->shown = 1;

//    card* newElement = ( card*) malloc(sizeof ( card));
//    newElement->value = valueFromCardName(input);
//    newElement->suit = suitFromCardName(input);
//    strcpy(newElement->name,input);
//    newElement->shown = 1;

    //newElement->data = *newCard;
    //printf("newcard->data.name: %s \n", newElement->data.name);
    //newElement->next = NULL;
    //for (int i = 0; i < 10; ++i) {
        push(stack,createCard(input));
        //top(*stack);
    //}
//    free(newCard);
//    newCard = NULL;
//    free(newElement);
//    newElement = NULL;
}

void cardsFromFile(card** stack){
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

//    while (fgets(str, MAXCHAR, fp) != NULL)
//        printf("%s\n", str);
    //shuffleList((card **) &stack);
    fclose(fp);


}



void interleave(card* first, card* second){
    card* tail = NULL;
    for (int i = 0; i < 52; ++i) {


        if (tail == NULL){
            tail = second;
        } else {
            tail ->next = second;
        }

        card* next = second->next;
        second->next = first;
        second = next;
        tail = first;

        next = first->next;
        first->next = NULL;
        first = next;
    }
}

/* iteratively track the first card of one of the lists onto the back of the list being built, then to switch which list is which */
void interleave_(card* first, card* second) {
    card* prev = NULL;
    /* Append the first card of 'second' to the list. */
    while (second != NULL){
        if (prev == NULL){
            prev = second;
        } else {
            prev ->next = second;
            prev = second;
        }
        /* cut the head of 'second' from 'second' */
        card* next = second ->next;
        second ->next = NULL;
        second = next;

        /* swap the two lists */
        card* temp = first;
        first = second;
        second = first;
    }
}
//void merge(struct card *p, struct card **q)
//{
//    struct card *p_curr = p, *q_curr = *q;
//    struct card *p_next, *q_next;
//
//    // While therre are avialable positions in p
//    while (p_curr != NULL && q_curr != NULL)
//    {
//        // Save next pointers
//        p_next = p_curr->next;
//        q_next = q_curr->next;
//
//        // Make q_curr as next of p_curr
//        q_curr->next = p_next; // Change next pointer of q_curr
//        p_curr->next = q_curr; // Change next pointer of p_curr
//
//        // Update current pointers for next iteration
//        p_curr = p_next;
//        q_curr = q_next;
//    }
//
//    *q = q_curr; // Update head pointer of second list
//}
struct card* interleave3(struct card* n1, struct card* n2){
    struct card *result, *temp1, *temp2;

    if (!n1){
        return n2;
    }
    if (!n2){
        return n1;
    }
    result = n1;
    while (n1 != NULL && n2 != NULL){
        temp1 = n1->next;
        temp2 = n2->next;

        if (n1->next)
            n2->next = n1->next;
        n1->next = n2;

        n1 = temp1;
        n2 = temp2;
    }
    return result;
}
struct card* interleave5(struct card *first, struct card *second){
    struct card *temp = NULL;
    struct card *result = NULL;

    result = first;
    temp = first;

    for (int i = 0; i < 52; ++i) {
        temp = temp->next;
        temp->next = second;
        temp = second;
        temp = temp->next;
        temp->next = first;
        temp = first;
    }
    temp->next = result;
    return result;
}

struct card* interleave4(struct card *first, struct card *second){
    struct card *temp = NULL;
    struct card *result = NULL;

    result = first;
    temp = first;

    while (temp ->next != first)
        temp = temp->next;
    temp->next = second;
    temp = second;
    while (temp->next != second)
        temp = temp->next;
    temp->next =result;
    return result;
}


/* first, split the list in half; second, shuffle the elements together. */
void shuffleList(card** stack){
    if (* stack == NULL) return;
    struct card *head = NULL;
    struct card *head1 = NULL;
    struct card *head2 = NULL;

    printf("\n");
    printf("before: \n");
    printList(*stack);
    printf("\n\n");
    splitList(*stack, &head1, &head2);

    printf("first half\n");
    printList(head1);
    printf("\n\n");
    printf("second half\n");
    printList(head2);

    head = interleave5(head1,head2);
    //merge(head2,&head1);
    //interleave4(head1,head2);
    printf("\n\n");
    printf("merged \n");
    printList(head);

    //split((struct card *) stack, &stack1, &stack2);

//    struct card half = splitList((struct card *) head, &head1, &head2);
//    interleave(*head, half);
//    *head = half;


    //printList((struct card *) stack);
}

