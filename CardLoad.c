//
// Created by Emil Trangeled on 15-04-2021.
// Edit Nicolai B Kragh 

#include <stdio.h>
#include <stdlib.h>
#include "CardFunctions.h"
#include <string.h>
#include <ctype.h>
#include <mmcobj.h>
#include <time.h>

//#define MAXCHAR 1000


/**
 * gets the int value of the ASCII char of a cards value
 * @author s185205 Nicolai B. Kragh
 * @param name - string with name of card 
 * @return int of the cards value
 */
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
/**
 * gets the char of a cards suit ("D" "H" "C" "S")
 * @author s185205 Nicolai B. Kragh
 * @param name - string with name of card 
 * @return the second char in the name string
 */
char suitFromCardName(char* name){
    return *(name+1);
}
/**
 * creates a new card , and gives it default values, and makes it double linked to itself
 * @author s185205 Nicolai B. Kragh
 * @param input - string with the name of the card 
 * @return returner - a pointer to the new card
 */
card* createCard(char* input){ 
    struct card *ptr1 = (card *)malloc(sizeof(card));
    ptr1->value = valueFromCardName(input);
    ptr1->suit = suitFromCardName(input);
    strcpy(ptr1->name, input);
    ptr1->shown = 1;
	ptr1->next = ptr1;
	ptr1->prev = ptr1;
    return ptr1;
}

/**
 * function to add a new node/card to the end of a stack. It also makes the last node point to the first node, and the first node's previous node point to the new node
 * in order to make the linked list cyclic
 * @author s186333 Stig Bødtker Petersen
 * @param start - the current stack
 * @param inCard - the new card to be added to the stack
 */
void push(card **start, card* inCard){
    if (*start == NULL || (*start)->next == NULL || (*start)->prev == NULL ){
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


/**
 * function to count the amount of nodes there are in a cyclic linked list
 * @author s186333 Stig Bødtker Petersen
 * @param head - the stack thats the be counted
 * @return result - the int value for the amount of nodes in the given stack
 */
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
/**
 * runs through all elements of the list and frees the memory they point at.
 * @author s185205 Nicolai B. Kragh
 * @param list - pointer to the head of the list
 * @return returner - a pointer to a head of a new empty list
 */
card* emptyStack(card* list){
   char count = countNodes(list);
   for (size_t i = 0; i < count; i++)
   {
	   list = list->next;
	   free(list);
   }
   card* returner = (card *)(malloc(sizeof(card)));
   returner->next = returner->prev = NULL;
   return returner;
}
/**
 * Function to print nodes/card name in a given Circular linked list
 * @author s186333 Stig Bødtker Petersen
 * @param head - the given stack to be printed
 */
void printList(struct card *head){

    //struct card *temp = head;
    for (int i = 0; i < countNodes(head); ++i) {
        printf("%s ", head->name);
        //printf("\n");
        head = head->next;
    }

}
/**
 * removes the top node in the given stack
 * @author s186333 Stig Bødtker Petersen
 * @param stack - the stack of cards
 */
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
/**
 * prints the name of the card in the top of the stack
 * @author s186333 Stig Bødtker Petersen
 * @param stack - the stack of cards
 */
void top(card* stack){
    if (stack != NULL){
        printf("Element on top: %s\n", stack ->name);
    } else {
        printf("The Stack is empty.\n");
    }
}
/**
 * function to split a linked list in two equal halves, and add each of the halves to a new linked list separately.
 *
 * The function sends two pointers ahead, one slow one fast, and when the fast reaches the end the slow pointer have reached the middle
 * and then cuts the list from where the middle is.
 * @author s186333 Stig Bødtker Petersen
 * @param head - The original linked list with nodes/cards
 * @param head1_ref - An empty linked list used to transfer the first half to
 * @param head2_ref - An empty linked list used to transfer the second half to
 */
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

/**
 * Reads a .txt file and loads every line in the file into a linked list of cards
 * @author Emil Nymark Trangeled - s195478 100%.
 * @param stack, The linked list to bed written to.
 */
void cardsFromFile(card** stack, char* filename){
    FILE *fRead;
    char str[4];
    char* dfilename = "..\\defaultDeck.txt";

    if (filename[0] == '\0'){
        filename = dfilename;
    }

    fRead = fopen(filename, "r");
    if (fRead == NULL){
        filename = "defaultDeck.txt"; // prøv at kigge efter filen i samme mappe stedet for
        fRead = fopen(filename, "r");
        if (fRead == NULL){
            printf("Could not open file, default cards loaded.\n");
            filename = dfilename;
            fRead = fopen(filename, "r");
        }
    }

    if (fRead) {
        for (int i = 0; i < 52; ++i) {
            if (fgets(str, 4, fRead) != NULL) {
                str[strlen(str) - 1] = '\0';
                push(stack, createCard(str));
            }
        }
    } else {
        printf("Could not open file %s\n", filename);
    }
    fclose(fRead);
}

/**
 * Writes all cards from the given linked list into a file.
 * @author Emil Nymark Trangeled - s195478 100%.
 * @param cards, The linked list of cards
 * @param filename, If the name is NULL it will make a file called cards.txt
 *                  else it will name a file the given name including .txt at the end.
 */
void cardsToFile(struct card *cards, char* filename){
    FILE *fwrite;
    char* dFilename = "cards.txt";

    if (filename[0] == '\0'){
        filename = dFilename;
    }

    fwrite = fopen(filename,"w");

    if (fwrite){

        for (int i = 0; i < 52; ++i) {

            fputs(cards->name, fwrite);
            fputs("\n",fwrite);
            cards = cards->next;
        }

    }
    else{
        printf("Failed to open file\n");
    }
    fclose(fwrite);

}
/**
 * Function to merge two linked list into one linked list in a interleaved manner (Ex: stack1= 1->3->5 stack2= 2->4->6 result= 1->2->3->4->5->6)
 * The function inserts the second linked list into the first linked list
 * @author s186333 Stig Bødtker Petersen
 * @param first - the first linked list
 * @param second - the second linked list to be merged into the first linked list
 * @return the first linked list merged with the the second linked list
 */
struct card* interleave(struct card *first, struct card *second){

    for (int i = 0; i < 25; ++i) {

        second = second->next;
        second->prev->prev = first;
        second->prev->next = first->next;
        first->next = second->prev;
        first = first->next->next;
        first->prev = second->prev;

    }
    second->prev = first;
    second->next = first->next;
    first->next = second;
    first = first->next->next;

    return first;
}
/**
 * function that performs the shuffle list function a random number of times, in order to create a pseudo random shuffled deck of cards
 * @author s186333 Stig Bødtker Petersen
 * @param head - the stack of nodes/cards
 * @return the randomized stack of nodes/cards
 */

struct card* randomShuffle(struct card* head){

    time_t t ;
    srand((unsigned ) time(&t));
    //struct card *head = NULL;
    struct card *head1 = NULL;
    struct card *head2 = NULL;

    int randomNum = rand() % 10000 + 3;

    // test a new random funktion
    for (int i = 0; i < 3*randomNum; ++i) {
        randomNum = rand() % 10000 + 10;
        splitList(head, &head1, &head2);
        head = interleave(head1,head2);
        for (int j = 0; j < randomNum; ++j) {
            head = head->next;
        }
    }
    return head;
}
/**
 * function to split the linked list stack in two equal halves an merges them again in a interleaved manner
 * @author s186333 Stig Bødtker Petersen
 * @param stack - the linked list of nodes/cards that is to be shuffled
 * @return the newly shuffled linked list
 */
/* first, split the list in half; second, shuffle the elements together. */
struct card* shuffleList(card** stack){
    struct card *head = NULL;
    struct card *head1 = NULL;
    struct card *head2 = NULL;
//    printf("\n");
//    printf("before: \n");
//    printList(*stack);
//    printf("\n\n");
    splitList(*stack, &head1, &head2);

//    printf("first half\n");
//    printList(head1);
//    printf("\n\n");
//    printf("second half\n");
//    printList(head2);

    head = interleave(head1,head2);
//    printf("\n\n");
//    printf("merged \n");
//    printList(head);

    return head;

}
/**
 * checks if a Game Move is valid, and if so executes it.
 * @author s185205 Nicolai B. Kragh
 * @param name - string with the name of the card, can be empty
 * @param fromIndex - index in the C or F Array where the From list is found 
 * @param toIndex - index in the C or F Array where the To list is found
 * @param fromType - string that indicates if From list is a Column or a Foundation
 * @param fromType - string that indicates if To list is a Column or a Foundation
 * @return int - 0 if the move is valid and it has been executed, a negative number if not.
 */
int fromStackToOther(char* name, char fromIndex, char toIndex, char* fromType, char* toType){
	card** from;
	card** to; 
	if(*fromType == 'C'){ 
		from = &C[fromIndex]; 
	}else{ 
		from = &F[fromIndex];
	}
	if(*toType == 'C'){ 
		to = &C[toIndex]; 
	}else{ 
		to = &F[toIndex]; 
	}
	char countFrom = countNodes(*from);
	card* cardWithName = NULL;
	card* fromCopy = *from;

// FINDS THE CARD IN FROM LIST AND VALIDATE
	if(countFrom == 0){
		return -1; //no cards in the From list
	}
	if (name[0] == '\0' ){ 
		// if name string parameter is empty then set last card in From list to be moved
		cardWithName = fromCopy->prev;
	} else {//if name string parameter is not empty then find that card in From list
		for (size_t i = 0; i < countFrom; i++){
			
			if(strcmp(fromCopy->name, name) == 0){
				cardWithName = fromCopy;
			}
			fromCopy = fromCopy->next;
		}
	}
	fromCopy = fromCopy->prev; // save last card in From list for later
	
	if(cardWithName == NULL){
		return -2; //the card wasnt found in From list
	}
	if(*fromType =='F' || *toType == 'F'){
		if(cardWithName != (*from)->prev){
			return -3; //only the last card of a list can be moved to or from a Foundation list
		}
	}
	
// VALIDATE IF CARD CAN BE MOVED TO THE TO LIST
	char countTo = countNodes(*to);

	if(countTo > 0){
		if(*toType == 'F'  && (
			cardWithName->value != ((*to)->prev->value)+1 ||
			cardWithName->suit != (*to)->prev->suit) ){
			return -4;  //the card wasnt one 1 larger than the last card of the Foundation list
						//or didnt have the same suit
		}
		if( *toType == 'C' && 
			(cardWithName->value != ((*to)->prev->value)-1 ||
			cardWithName->suit == ((*to)->prev->suit)) ){
			return -5; 	//the card wasnt one 1 smaller than the last card of the Column list
						//or had the same suit
		}
	}

// ALL CHECKED - READY TO GO
	if(countFrom == 1){
		*from = NULL; //Empties the the From list if it only had one card prior to the move
	}else{
		cardWithName->prev->next = *from; // double links the new end of the From list to its head
		(*from)->prev= cardWithName->prev;
		if((*from)->prev->shown == 0) (*from)->prev->shown = 1; 
	}
	if( countTo == 0){
		*to = cardWithName;
		(*to)->prev = (*to)->next = *to;
	}else{
		cardWithName->prev = (*to)->prev; //inserts the card (and any trailing cards) into the To list
		fromCopy->next = *to;
		(*to)->prev->next = cardWithName; 
		(*to)->prev = fromCopy;
	}
	return 0;
}

