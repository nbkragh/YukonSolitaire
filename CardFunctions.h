//
// Created by Emil Trangeled on 15-04-2021.
// Edit Nicolai B. Kragh

#ifndef YUKONSOLITAIRE_CARDFUNCTIONS_H
#define YUKONSOLITAIRE_CARDFUNCTIONS_H
//#include <stdio.h>
typedef struct Card {
    int  value;     // værdien 1-13 (A1..10JQK)
    int shown;      // boolean for synlig / ikke synlig
    char suit;      // Heart Diamond Spades Clubs
    char name[2];   // String format af value+suit f.eks. "AC" , "7H" , "KC", "TS"
    
} card;

typedef struct element {
    int key;
    struct Card data;
    struct element* next;
} element;
void push( element*, element*);
void LoadCard(char *, element*);
void cardsFromFile( element*);
void displayGame(void);
void top (element*);

#endif //YUKONSOLITAIRE_CARDFUNCTIONS_H

