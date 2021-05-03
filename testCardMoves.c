#include "CardFunctions.h"
#include <stdio.h>
#include <stdlib.h>
int main() {
 // populate C[]
    // populate F[]
    for (size_t i = 0; i < 4; i++) {
        F[i] = NULL;
	}  
	cardsFromFile(&stack);
	//displayAllCards(0);
	//displayAllCards(1);
	dealCardsToGame(stack);
	//printBoard();
	printf("\n fromStackToOther(\"AH\", &C[2], &F[0], \"C\",\"F\") : %i\n", fromStackToOther("AH", &C[2], &F[0], "C","F"));
	printBoard();
	printf("\n fromStackToOther(\"QH\", &C[2], &F[0], \"C\",\"F\") : %i\n", fromStackToOther("QH", &C[2], &F[0], "C","F"));
	printBoard();
	printf("\n fromStackToOther(\"QH\", &F[0], &F[1], \"F\",\"F\") : %i\n", fromStackToOther("QH", &F[0], &F[1], "F","F"));
	printBoard();
	printf("\n fromStackToOther(\"6H\", &C[1], &F[1], \"C\",\"F\") : %i\n", fromStackToOther("6H", &C[1], &F[1], "C","F"));
	printBoard();
	printf("\n fromStackToOther(\"JS\", &C[5], &F[1], \"C\",\"F\") : %i\n", fromStackToOther("JS", &C[5], &F[1], "C","F"));
	printBoard();
	printf("\n fromStackToOther(\"KS\", &C[6], &F[2], \"C\",\"F\") : %i\n", fromStackToOther("KS", &C[6], &F[2], "C","F"));
	printBoard();
	printf("\n fromStackToOther(\"KS\", &F[2], &F[1], \"F\",\"F\") : %i\n", fromStackToOther("KS", &F[2], &F[1], "F","F"));
	printBoard();
	printf("\n fromStackToOther(\"4S\", &C[3], &F[0], \"C\",\"F\") : %i\n", fromStackToOther("4S", &C[3], &F[0], "C","F"));
	printBoard();
	printf("\n fromStackToOther(\"KH\", &C[3], &F[1], \"C\",\"F\") : %i\n", fromStackToOther("KH", &C[3], &F[1], "C","F"));
	printBoard();
	printf("\n fromStackToOther(\"JS\", &C[3], &F[1], \"C\",\"C\") : %i\n", fromStackToOther("JS", &C[5], &C[6], "C","C"));
	printBoard();
	printf("\n fromStackToOther(\"7S\", &C[6], &C[3], \"C\",\"C\") : %i\n", fromStackToOther("7S", &C[6], &C[3], "C","C"));
	printBoard();
	printf("\n fromStackToOther(\"3S\", &C[6], &F[3], \"C\",\"F\") : %i\n", fromStackToOther("3S", &C[6], &F[3], "C","F"));
	printBoard();

}