#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "CardFunctions.h"

char returnMsg[50] = "OK";

void noParameterMsg(char *command);

int main() {
    card * stack = NULL;

    // populate C[]

    for (size_t i = 0; i < 7; i++) {
        C[i] = NULL;
    }
    // populate F[]
    for (size_t i = 0; i < 4; i++) {
        F[i] = NULL;
    }

/*
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
    cardsToFile(stack, NULL);
    displayGame();

    card* newCard = (card*)malloc(sizeof(card));

    stack = NULL;
    top(stack);
	*/



    setbuf(stdout, 0);
    //stack = (card*)(malloc(sizeof(card)));
    //cardsFromFile(&stack);
    char tInput[inputSize] = "",lastCommand[inputSize] = "";
    char command[3]="",parameter[25]="";
    char *pTokens[2];
    int i;

    while (strcmp(tInput, "QQ") != 0) {
        printBoard();
        // iterator for pTokens pointer array.
        i = 0;
        // printing the pTokens
        printf("LAST Command: %s\n", lastCommand);
        // printing the error message or just OK if everything went ok.
        printf("Message: %s\n", returnMsg);
        // Printing the input field
        printf("INPUT >");
        // Scanning for a string. It reads until it encounters a newline "\n".
        // See explanation for method 3:
        // https://www.geeksforgeeks.org/taking-string-input-space-c-3-different-methods/#:~:text=We%20can%20take%20string%20input,the%20form%20of%20user%20input.
        scanf("%[^\n]%*c", tInput);

        // Copies the input to the last pTokens for it
        // to be displayed in the next iteration of the while loop
        strcpy(lastCommand, tInput);

        // Splits the input into two different string pointers
        char *ptr = strtok(tInput, " ");

        pTokens[1] = "";
        // Assigns the two string pointers to pToken array
        while (ptr) {
            pTokens[i++] = ptr;
            ptr = strtok(NULL, " ");
        }
        // Copies the two strings to command and parameter
        strcpy(command, pTokens[0]);
        strcpy(parameter, pTokens[1]);


        // Converts the command to uppercase, to prevent errors when inputting commands.
        for(int j = 0; command[j]; j++){
            command[j] = toupper(command[j]);
        }

        // Looks through all the commands and executes the commands accordingly
        if (strcmp(command, "LD") == 0){
            printf("LOADING CARDS FROM: %s\n\n", parameter);
            strcpy(returnMsg, "OK");
            cardsFromFile(&stack);
            prepareShowStack(stack, 0);
        }
        else if (strcmp(command, "SW") == 0){
            // Checks if the command SW has a parameter entered, if it has it will return an error.
            // If not it will run the command.
            if (strcmp(parameter,"") == 0){
                printf("SHOWING CARDS\n\n");
                strcpy(returnMsg, "OK");

                turnAllCards();
            } else {
                //strcpy(returnMsg, "Command (SW) does not have a parameter!");
                noParameterMsg(command);
                pTokens[1] = "";
            }

        }
        else if (strcmp(command, "SL") == 0){
            printf("SPLITTING CARDS FROM: %s\n\n", parameter);
            strcpy(returnMsg, "OK");
            shuffleList(&stack);
            for (size_t j = 0; j < 7; j++) {
                C[j] = emptyStack(C[j]);
            }
            prepareShowStack(stack, 0);
        }
        else if (strcmp(command, "SR") == 0){
            if (strcmp(parameter,"") == 0){
                printf("SHUFFLING THE CARDS\n\n");
                strcpy(returnMsg, "OK");
            } else {
                noParameterMsg(command);
                pTokens[1] = "";
            }

        }
        else{
            strcpy(returnMsg,"COMMAND NOT FOUND");
        }
    }



}

void noParameterMsg(char *command){
    char str[100];
    strcat(str, "Command (");
    strcat(str, command);
    strcat(str, ") does not have a parameter!");
    strcpy(returnMsg, str);
}


