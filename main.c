#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CardFunctions.h"

void printBoard(void);
void prepareShowStack(card *, char);
void dealToCStacks(card *);
card *C[7];
card *F[4];
card *stack = NULL;
char play = 0;  // bool for om programmet er i play-state eller ej
int main() {
    // populate C[]
    for (size_t i = 0; i < 7; i++) {
        C[i] = (card *)(malloc(sizeof(card)));
		C[i]->next = C[i]->prev = NULL;
    }
    // populate F[]
    for (size_t i = 0; i < 4; i++) {
        F[i] = (card *)(malloc(sizeof(card)));
		F[i]->next = F[i]->prev = NULL;
	}

    cardsFromFile(&stack);

    prepareShowStack(stack, 0);
    printBoard();
    // tømmer hver C[i] og genopretter en ny head pointer deri
    for (size_t i = 0; i < 7; i++) {
        C[i] = emptyStack(C[i]);
    }

    prepareShowStack(stack, 1);
    printBoard();
    for (size_t i = 0; i < 7; i++) {
        C[i] = emptyStack(C[i]);
    }

    dealToCStacks(stack);
    printBoard();

	setbuf(stdout, 0);

    card* newCard = (card*)malloc(sizeof(card));

    stack = NULL;
    top(stack);
    stack = (card*)(malloc(sizeof(card)));
    cardsFromFile(&stack);
    displayGame();
}

// fordeler den originale stak af kort ud på C stakkene, så alle kortene
// kan vises på boardet
void prepareShowStack(card *s, char shown) {
    card *currentCard = s;
    for (size_t i = 0; i < 52; i++) {// kan antage at stack.length er 52 pga. input validering
		card *newCard = createCard(currentCard->name);
		newCard->shown = shown;
        push(&C[i % 7], newCard);  
        currentCard = currentCard->next;
    }

}

void dealToCStacks(card *s) {
    card *currentCard = s;
    push(&C[0], createCard(currentCard->name));
    currentCard = currentCard->next;
    for (size_t i = 1; i < 12; i++) {
        for (size_t j = 1; j < 7; j++) {
            if (i <= j + 5) {
                card *newCard = createCard(currentCard->name);
                push(&C[j], newCard);
                currentCard = currentCard->next;
                if (i <= j) {
                    newCard->shown = 0;
                }
            }
        }
    }

    free(currentCard);
    currentCard = NULL;
}

void printBoard() {
    card *copyC[7];
    for (size_t i = 0; i < 7; i++) {
        copyC[i] = C[i];
    }
    printf("\nC1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    size_t f = 0;
    size_t nextLine = 1;
    while (nextLine) {
        for (size_t i = 0; i < 7; i++) {
            // hvis alle kortene i C-stakken allerede er printet så print intet
            if (copyC[i] != NULL) {
                copyC[i]->shown == 0 ? printf("[]\t") : printf("%s\t", copyC[i]->name);
                nextLine = 1;
                if (copyC[i]->next == C[i]) {
                    copyC[i] = NULL;
                } else {
                    copyC[i] = copyC[i]->next;
                }
            } else {
                printf("\t");
                nextLine = 0;
            }
            if (i == 6) {  //hvis det er efter C7 så skift linie eller print F[]
                if (f % 2 == 0 && f < 7) {
					char fvalue[3] = "[]";
					
					if(F[(f/2)]->name == NULL) {
						strcpy(fvalue, F[f/2]->name);
					}
					printf("\t%s\tF%i\n", fvalue,f/2);
                } else {
                    printf("\n");
                }
            }
        }
		f++;
    }
}

int main(){


}
