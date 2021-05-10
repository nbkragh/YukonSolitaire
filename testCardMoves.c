#include "CardFunctions.h"
#include <stdio.h>
#include <stdlib.h>
int main() {
 // populate C[]
    // populate F[]
    for (size_t i = 0; i < 4; i++) {
        F[i] = NULL;
	}  
	cardsFromFile(&stack, "dealCardsToGame.txt");
	dealCardsToGame(stack);
	printf("TC22------------------------------------------------------\n");
	printf("\n C1:AC->F1 : %i\n", fromStackToOther("AC", 0, 0, "C","F"));
	printBoard();
	printf("\n F1:AC->C1 : %i\n", fromStackToOther("AC", 0, 0, "F","C"));
	printBoard();
	printf("\n C1->F1 : %i\n", fromStackToOther("", 0, 0, "C","F"));
	printBoard();
	printf("\n F1->C1 : %i\n", fromStackToOther("", 0, 0, "F","C"));
	printBoard();
	printf("TC23-----------------------------------------------------\n");
	printf("\n C3->C7 : %i\n", fromStackToOther("", 2, 6, "C","C"));
	printBoard();
	printf("\n C4->F1 : %i\n", fromStackToOther("", 3, 0, "C","F"));
	printBoard();
	printf("\n C5->F2 : %i\n", fromStackToOther("", 4, 1, "C","F"));
	printBoard();
	printf("\n C5->F1 : %i\n", fromStackToOther("", 4, 0, "C","F"));
	printBoard();
	printf("\n F1->C2 : %i\n", fromStackToOther("", 0, 1, "F","C"));
	printBoard();
	printf("TC24-----------------------------------------------------\n");
	printf("\n C6:9S->F1 : %i\n", fromStackToOther("9S", 5, 0, "C","F"));
	printBoard();
	printf("\n C7:QS->C4 : %i\n", fromStackToOther("QS", 6, 3, "C","C"));
	printBoard();
	printf("\n C2:5S->F1 : %i\n", fromStackToOther("5S", 1, 0, "C","F"));
	printBoard();
	printf("TC25-----------------------------------------------------\n");
	printf("\n C2:QS->C3 : %i\n", fromStackToOther("QS", 1, 2, "C","C"));
	printBoard();
	printf("\n F2->C3 : %i\n", fromStackToOther("", 1, 2, "F","C"));
	printBoard();
	printf("\n F1->C3 : %i\n", fromStackToOther("", 0, 2, "F","C"));
	printBoard();
	printf("\n C6:6S->C3 : %i\n", fromStackToOther("6S", 5, 2, "C","C"));
	printBoard();
	printf("TC26-----------------------------------------------------\n");
	printf("\n C5->F3 : %i\n", fromStackToOther("", 4, 2, "C","F"));
	printBoard();
	printf("\n C2->F1 : %i\n", fromStackToOther("", 1, 0, "C","F"));
	printBoard();
	printf("\n F1->F3 : %i\n", fromStackToOther("", 0, 2, "F","F"));
	printBoard();
	printf("\n F1->F2 : %i\n", fromStackToOther("", 0, 1, "F","F"));
	printBoard();
	printf("\n C6->F3 : %i\n", fromStackToOther("", 5, 2, "C","F"));
	printBoard();


}