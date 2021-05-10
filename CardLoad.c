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
// returnerer et ny head til den tømte stack
card* emptyStack(card* stack){
   card* nextS;
   char count = countNodes(stack);
   for (size_t i = 0; i < count; i++)
   {
	   nextS = stack->next;
	   free(stack);
	   stack = nextS;
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
    FILE *fp;
    char str[4];
    char* dfilename = "..\\defaultDeck.txt";


    if (filename[0] == '\0'){
        filename = dfilename;
    }

    fp = fopen(filename, "r");
    if (fp == NULL){
        filename = "defaultDeck.txt"; // prøv at kigge efter filen i samme mappe stedet for
        fp = fopen(filename, "r");
        if (fp == NULL){
            printf("Could not open file %s\n", filename);
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 13; ++j) {
            if (fgets(str, 4, fp) != NULL){
                str[strlen(str)-1] = '\0';
                push(stack,createCard(str));
            }
        }
    }
    fclose(fp);
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
    char* dFilename = "..\\cards.txt";

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

int fromStackToOther(char* name, char fromIndex, char toIndex, char* fromType, char* toType){
	card** from;
	card** to; 
	if(*fromType == 'C'){ from = &C[fromIndex]; }else{ from = &F[fromIndex];}
	if(*toType == 'C'){ to = &C[toIndex]; }else{ to = &F[toIndex]; }
	char countFrom = countNodes(*from);
	card* cardWithName = NULL;
	card* fromCopy = *from;

	if(countFrom == 0){
		return -1; //ingen kort i from stack
	}
	if (name[0] == '\0' ){ 
		// hvis input ikkke indeholder et bestemt kort der skal flyttes fra, så flyt sidte kort i stakken
		cardWithName = fromCopy->prev;
	} else {
		for (size_t i = 0; i < countFrom; i++){
			//finder kortet der skal flyttes fra "from" stakken
			if(strcmp(fromCopy->name, name) == 0){
				cardWithName = fromCopy;
			}
			fromCopy = fromCopy->next;
		}
	}
	
	fromCopy = fromCopy->prev; // gemmer sidste kort i stakken til senere
	
	if(cardWithName == NULL){
		return -2; //kort fandtes ikke i stakken 
	}
	if(*fromType =='F' || *toType == 'F'){
		if(cardWithName != (*from)->prev){
			return -3; //kun øverste kort kan flyttes fra eller til en F[] stak
		}
	}
	
	char countTo = countNodes(*to);

	if(countTo > 0){
		if(*toType == 'F'  && (
			cardWithName->value != ((*to)->prev->value)+1 ||
			cardWithName->suit != (*to)->prev->suit) ){
			return -4;  //kortet var ikke 1 større end toppen af F[] stakken 
						//eller havde ikke samme kulør
		}
		if( *toType == 'C' && 
			(cardWithName->value != ((*to)->prev->value)-1 ||
			cardWithName->suit == ((*to)->prev->suit)) ){
			return -5; 	//kortet var ikke 1 mindre end bunden af C[] stakken 
						//eller havde samme kulør
		}
	}

// ALT TJEKKET - READY TO GO
	if(countFrom == 1){
		*from = NULL; //tømmer stakken
	}else{
		cardWithName->prev->next = *from; // binder from stakken sammen efter fjernet et kort
		(*from)->prev= cardWithName->prev;
		if((*from)->prev->shown == 0) (*from)->prev->shown = 1; 
	}
	if( countTo == 0){
		*to = cardWithName;
		(*to)->prev = (*to)->next = *to;
	}else{
		cardWithName->prev = (*to)->prev; //linker nye kort til "to" stakken
		fromCopy->next = *to;
		(*to)->prev->next = cardWithName; // linker "to" stakken til nye kort
		(*to)->prev = fromCopy;
	}
	return 0;
}

