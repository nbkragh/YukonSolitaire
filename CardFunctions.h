//
// Created by Emil Trangeled on 15-04-2021.
//

#ifndef YUKONSOLITAIRE_CARDFUNCTIONS_H
#define YUKONSOLITAIRE_CARDFUNCTIONS_H
//#include <stdio.h>
typedef struct Card {
    int  value;     // værdien 1-13 (A1..10JQK)
    char suit;      // Heart Diamond Spades Clubs
    char name[2];   // String format af value+suit f.eks. "AC" , "7H" , "KC", "TS"
    int shown;      // boolean for synlig / ikke synlig
} card;

typedef struct element {
    struct Card data;
    int key;
    struct element* next;
} element;
void LoadCard(char *, element**);
void cardsFromFile( element**);
void displayGame(void);
void top (element*);


#endif //YUKONSOLITAIRE_CARDFUNCTIONS_H

