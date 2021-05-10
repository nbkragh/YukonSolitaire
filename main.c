#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "CardFunctions.h"

char returnMsg[50] = "OK";

void noParameterMsg(char *command);
/**
 * @author Emil Nymark Trangeled - s195478 80%, Stig Bødtker Petersen - s186333 10%,  Nicolai B. Kragh - s185205 10%.
 * Creates the input command text and allows commands to be entered.
 * If commands with no parameters are entered it will return a descriptive error message.
 * If unknown commands are entered it will say so.
 * @return void
 */
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


    setbuf(stdout, 0);

    char tInput[inputSize] = "",lastCommand[inputSize] = "";
    char command[15]="",parameter[25]="";
    char *pTokens[2];
    int i, gameState = 0;

    while (strcmp(command, "QQ") != 0) {
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
        if(gameState == 0) {
            // Looks through all the commands and executes the commands accordingly
            if (strcmp(command, "LD") == 0) {
                //printf("LOADING CARDS FROM: %s\n\n", parameter);
                strcpy(returnMsg, "OK - CARDS LOADED");
                emptyDisplayColumns();

                cardsFromFile(&stack, parameter);

                prepareShowStack(stack, 0);
            } else if (strcmp(command, "SW") == 0) {
                // Checks if the command SW has a parameter entered, if it has it will return an error.
                // If not it will run the command.
                if (strcmp(parameter, "") == 0) {
                    //printf("SHOWING CARDS\n\n");
                    strcpy(returnMsg, "OK - SHOWING CARDS");

                    turnAllCards();
                } else {
                    //strcpy(returnMsg, "Command (SW) does not have a parameter!");
                    noParameterMsg(command);
                    pTokens[1] = "";
                }

            } else if (strcmp(command, "SI") == 0) {
                //printf("SPLITTING CARDS FROM: %s\n\n", parameter);
                strcpy(returnMsg, "OK - CARD HAVE BEEN SPLIT");
                shuffleList(&stack);
                emptyDisplayColumns();
                prepareShowStack(stack, 0);

            } else if (strcmp(command, "SR") == 0) {
                if (strcmp(parameter, "") == 0) {
                    //printf("SHUFFLING THE CARDS\n\n");
                    strcpy(returnMsg, "OK - SHUFFLED THE CARDS");
                    randomShuffle(stack);
                    emptyDisplayColumns();

                    prepareShowStack(stack, 0);

                } else {
                    noParameterMsg(command);
                    pTokens[1] = "";
                }

            } else if (strcmp(command, "SD") == 0) {
                    strcpy(returnMsg, "OK - SAVED CURRENT CARDS TO FILE");
                    cardsToFile(stack, parameter);


            } else if (strcmp(command, "P") == 0) {
                if (strcmp(parameter, "") == 0) {
                    //printf("PREPARING GAME\n\n");
                    strcpy(returnMsg, "OK - GAME READY TO PLAY");
                    emptyDisplayColumns();
                    dealCardsToGame(stack);
                    gameState = 1;

                } else {
                    noParameterMsg(command);
                    pTokens[1] = "";
                }

            } else {
                strcpy(returnMsg, "COMMAND NOT FOUND");
            }
        } else if (gameState == 1) {
            if (strcmp(command, "Q") == 0) {
                if (strcmp(parameter, "") == 0) {
                   // printf("Quitting current game\n\n");
                    strcpy(returnMsg, "OK - QUIT CURRENT GAME");
                    gameState = 0;

                } else {
                    noParameterMsg(command);
                    pTokens[1] = "";
                }

            } else if (command[0] == 'C' || command[0] == 'F') {

				char name[3] = "\000";
				char fromIndex;
				char toIndex;
				char fromType =command[0];
				char toType = command[strlen(command) - 2];


				
				if(fromType == 'C'){
					fromIndex = command[1]-49;
				}else{
					fromIndex= command[1]-49;
				}
				if(toType == 'C'){
					toIndex = (command[strlen(command) - 1])-49;
				}else{
					toIndex = (command[strlen(command) - 1])-49;
				}
				
				if( command[2]  == ':'){
					memcpy( name, &command[3], 2 );
					strcpy(&name[2] , "\0");
					
				}

				printf("fromStackToOther() : %i" , fromStackToOther(name, fromIndex, toIndex , &fromType, &toType));
                strcpy(returnMsg, "OK - MOVED CARD");

            } else {
                strcpy(returnMsg, "Game is started");
            }
        }



    }



}

/**
 * @author Emil Nymark Trangeled - s195478 100%.
 * Creates a string for the parameters that does not contain any parameter
 * and stores the error in returnMsg which is a global variable.
 * @param command, The command that does not contain any parameters.
 */
void noParameterMsg(char *command){
    char str[100];
    strcat(str, "Command (");
    strcat(str, command);
    strcat(str, ") does not have a parameter!");
    strcpy(returnMsg, str);
}


