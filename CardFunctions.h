//
// Created by Emil Trangeled on 15-04-2021.
// Edit Nicolai B. Kragh, Stig Bødtker Petersen

#ifndef YUKONSOLITAIRE_CARDFUNCTIONS_H
#define YUKONSOLITAIRE_CARDFUNCTIONS_H
//#include <stdio.h>
//typedef struct Card {
//    int  value;     // værdien 1-13 (A1..10JQK)
//    char suit;      // Heart Diamond Spades Clubs
//    char name[2];   // String format af value+suit f.eks. "AC" , "7H" , "KC", "TS"
//    int shown;      // boolean for synlig / ikke synlig
//} card;
//
//typedef struct card {
//    struct Card data;
//    int key;
//    struct card* next;
//} card;

/**
 * struct for the linked list, each node is to be used as a card.
 * Holds the value of the card, if the card is face down or up, the suit and the name of the card.
 * have two pointers one for the next in the linked list and the previous
 * @author s186333 Stig Bødtker Petersen, s185205 Nicolai B. Kragh
 */
typedef struct card {
    int  value;     // værdien 1-13 (A1..10JQK)
    int shown;      // boolean for synlig / ikke synlig
    char suit;      // Heart Diamond Spades Clubs
    char name[2];   // String format af value+suit f.eks. "AC" , "7H" , "KC", "TS"
    struct card *next;
    struct card *prev;
} card;

// "GLOBAL VARIABLES"
#define inputSize 25
card *C[7];
card *F[4];
card *stack;

char play; // er programmet i Game-state eller ej?



void LoadCard(char *, card**);
void cardsFromFile(card**, char* filename);
void top (card*);
struct card* shuffleList(card**);
struct card* randomShuffle(struct card* stack);
card* createCard(char*);
void push(card **, card*);
void cardsToFile(struct card *cards, char* filename);
card* emptyStack(card* );
int fromStackToOther(char*, char, char, char*, char*);
int displayGame(char * tInput, char * lastCommand);
void printBoard(void);
void dealCardsToGame(card* );
void prepareShowStack(card *s, char shown);
void turnAllCards();
int countNodes(struct card* head);
void emptyDisplayColumns();

#endif //YUKONSOLITAIRE_CARDFUNCTIONS_H

