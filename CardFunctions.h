//
// Created by Emil Trangeled on 15-04-2021.
// Edit Nicolai B. Kragh

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
typedef struct card {
    int  value;     // værdien 1-13 (A1..10JQK)
    int shown;      // boolean for synlig / ikke synlig
    char suit;      // Heart Diamond Spades Clubs
    char name[2];   // String format af value+suit f.eks. "AC" , "7H" , "KC", "TS"
    struct card *next;
} card;
void LoadCard(char *, card**);
void cardsFromFile(card**);
void displayGame(void);
void top (card*);
void shuffleList(card**);
card* createCard(char*);
void push(card **, card*);

#endif //YUKONSOLITAIRE_CARDFUNCTIONS_H

