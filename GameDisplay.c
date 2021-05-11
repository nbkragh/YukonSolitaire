//
// Created by Emil Trangeled on 15-04-2021.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "CardFunctions.h"
#define inputSize 25

//char returnMsg[50] = "OK";

//void noParameterMsg(char *command);

/**
 * @author Emil Nymark Trangeled - s195478
 * Creates the input command text and allows commands to be entered.
 * If commands with no parameters are entered it will return a descriptive error message.
 * If unknown commands are entered it will say so.
 * @return void
 */
//int displayGame(char * tInput, char * lastCommand) {
//
//    char command[3]="",parameter[25]="";
//    char *pTokens[2];
//    int i;
//
//
//    // while loop for the pTokens loop
//
//    // iterator for pTokens pointer array.
//    i = 0;
//    // printing the pTokens
//    printf("LAST Command: %s\n", lastCommand);
//    // printing the error message or just OK if everything went ok.
//    printf("Message: %s\n", returnMsg);
//    // Printing the input field
//    printf("INPUT >");
//    // Scanning for a string. It reads until it encounters a newline "\n".
//    // See explanation for method 3:
//    // https://www.geeksforgeeks.org/taking-string-input-space-c-3-different-methods/#:~:text=We%20can%20take%20string%20input,the%20form%20of%20user%20input.
//    scanf("%[^\n]%*c", tInput);
//
//    // Copies the input to the last pTokens for it
//    // to be displayed in the next iteration of the while loop
//    strcpy(lastCommand, tInput);
//
//    // Splits the input into two different string pointers
//    char *ptr = strtok(tInput," ");
//
//    // Assigns the two string pointers to pToken array
//    while (ptr){
//        pTokens[i++] = ptr;
//        ptr = strtok(NULL, " ");
//    }
//    // Copies the two strings to command and parameter
//    strcpy(command, pTokens[0]);
//    strcpy(parameter, pTokens[1]);
//
//    // Converts the command to uppercase, to prevent errors when inputting commands.
//    for(int j = 0; command[j]; j++){
//        command[j] = toupper(command[j]);
//    }
//
//    // Looks through all the commands and executes the commands accordingly
//    if (strcmp(command, "LD") == 0){
//        printf("LOADING CARDS FROM: %s\n\n", parameter);
//        strcpy(returnMsg, "OK");
//        cardsFromFile(&stack);
//    }
//    else if (strcmp(command, "SW") == 0){
//        // Checks if the command SW has a parameter entered, if it has it will return an error.
//        // If not it will run the command.
//        if (strcmp(parameter,"") == 0){
//            printf("SHOWING CARDS\n\n");
//            strcpy(returnMsg, "OK");
//        } else {
//            //strcpy(returnMsg, "Command (SW) does not have a parameter!");
//            noParameterMsg(command);
//            pTokens[1] = "";
//        }
//
//    }
//    else if (strcmp(command, "SL") == 0){
//        printf("SPLITTING CARDS FROM: %s\n\n", parameter);
//        strcpy(returnMsg, "OK");
//    }
//    else if (strcmp(command, "SR") == 0){
//        if (strcmp(parameter,"") == 0){
//            printf("SHUFFLING THE CARDS\n\n");
//            strcpy(returnMsg, "OK");
//        } else {
//            noParameterMsg(command);
//            pTokens[1] = "";
//        }
//
//    }
//    else{
//        strcpy(returnMsg,"COMMAND NOT FOUND");
//    }
//
//
//    return 0;
//}

/**
 * @author Emil Nymark Trangeled - s195478
 * Creates a string for the parameters that does not contain any parameter
 * and stores the error in returnMsg.
 * @param command The command that does not contain any parameters.
 */
//void noParameterMsg(char *command){
//    char str[100];
//    strcat(str, "Command (");
//    strcat(str, command);
//    strcat(str, ") does not have a parameter!");
//    strcpy(returnMsg, str);
//}


/**
 * readies the game board for displaying all cards in STARTUP phase, by copying the cards from the main list, 
 * and dealing them out to Column lists, each column per each row.
 * @author s185205 Nicolai B. Kragh
 * @param s - a pointer to the head of a list, it is intended to be the main list that all the imported cards resides in.
 * @param shown - a char that acts as a boolean to set the cards to be shown or not.
 * @return void
 */
void prepareShowStack(card *s, char shown) {
    card *currentCard = s;
    for (size_t i = 0; i < 52; i++) {// kan antage at stack.length er 52 pga. input validering
		card *newCard = createCard(currentCard->name);
		newCard->shown = shown;
        push(&C[i % 7], newCard);  
        currentCard = currentCard->next;
    }
}

void turnAllCards(){
    for (size_t i = 0; i < 7; i++) {
        int amount = countNodes(C[i]);
        for (int j = 0; j < amount; ++j) {
            C[i]->shown = !(C[i]->shown);
            C[i] = C[i]->next;
        }
    }
}
/**
 * readies the game board for PLAY phase by copying the cards from the main list, 
 * and dealing them out to Column lists, with increasing number of rows by column number.
 * @author s185205 Nicolai B. Kragh
 * @param s - a pointer to the head of a list, it is intended to be the main list, that all the imported cards resides in
 * @return void
 */
void dealCardsToGame(card *s) {
    card *currentCard = s;
    push(&C[0], createCard(currentCard->name)); // first column gets only one card
    currentCard = currentCard->next;
    for (size_t i = 1; i < 12; i++) {
        for (size_t j = 1; j < 7; j++) {
            if (i <= j + 5) { 
                card *newCard = createCard(currentCard->name);
                push(&C[j], newCard);
                currentCard = currentCard->next;
                if (i <= j) {  // if not last 5 cards in column then hide this card
                    newCard->shown = 0; 
                }
            }
        }
    }

}

void emptyDisplayColumns(){
    for (size_t j = 0; j < 7; j++) {
        C[j] = emptyStack(C[j]);
    }
}

/**
 * prints the game board part of the terminal output
 * @author s185205 Nicolai B. Kragh
 * @return void
 */
void printBoard() {
    card *copyC[7]; // copy all the Column lists, so the head of original list is not changed after looping
    for (size_t i = 0; i < 7; i++) {
        copyC[i] = C[i];
    }
    printf("\nC1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    char f = 0;				//used for counting iterations in while loop
    char nextLine = 1;		//and deciding when loop has to end
    while (nextLine) {
        if (f > 8){
            nextLine = 0; //minimum of 8 rows has been reached
        }
        for (size_t i = 0; i < 7; i++) {
            // if all cards in current list is already printet, then skip printing it
            if (copyC[i] != NULL) {
                copyC[i]->shown == 0 ? printf("[]\t") : printf("%s\t", copyC[i]->name);
                
                if (copyC[i]->next == C[i]) {
                    copyC[i] = NULL; //end of list has been reached
                } else {
                    copyC[i] = copyC[i]->next; //point to next element in list
					nextLine = 1;	// not done printing this list, so do not end while loop
                }
            } else {
                printf("\t");
            }
            if (i == 6) {  					// print a Foundation list element after C[6] element in current row
                if (f % 2 == 0 && f < 7) {  // but only every second row until row 8
					char fvalue[3] = "[]";
					if(F[(f/2)] != NULL) {
						strcpy(fvalue, F[f/2]->prev->name);
					}
					printf("\t%s\tF%i\n", fvalue,(f/2) + 1);
                } else {
                    printf("\n");
                }
            }
        }
		f++;
    }
}
