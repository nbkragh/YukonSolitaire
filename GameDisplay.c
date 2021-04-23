//
// Created by Emil Trangeled on 15-04-2021.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "CardFunctions.h"

#define inputSize 25

char returnMsg[50] = "OK";

void noParameterMsg(char *command);

/**
 * @author Emil Nymark Trangeled - s195478
 * Creates the input command text and allows commands to be entered.
 * If commands with no parameters are entered it will return a descriptive error message.
 * If unknown commands are entered it will say so.
 * @return void
 */
int displayGame(void) {

    char input[inputSize] ="",command[3]="",parameter[25]="", lastCommand[inputSize] = "";
    char *pTokens[2];
    int i;


    // while loop for the pTokens loop
    while (strcmp(input, "QQ") != 0) {
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
        scanf("%[^\n]%*c", input);

        // Copies the input to the last pTokens for it
        // to be displayed in the next iteration of the while loop
        strcpy(lastCommand, input);

        // Splits the input into two different string pointers
        char *ptr = strtok(input," ");

        // Assigns the two string pointers to pToken array
        while (ptr){
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
        }
        else if (strcmp(command, "SW") == 0){
            // Checks if the command SW has a parameter entered, if it has it will return an error.
            // If not it will run the command.
            if (strcmp(parameter,"") == 0){
                printf("SHOWING CARDS\n\n");
                strcpy(returnMsg, "OK");
            } else {
                //strcpy(returnMsg, "Command (SW) does not have a parameter!");
                noParameterMsg(command);
                pTokens[1] = "";
            }

        }
        else if (strcmp(command, "SL") == 0){
            printf("SPLITTING CARDS FROM: %s\n\n", parameter);
            strcpy(returnMsg, "OK");
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
    return 0;
}

/**
 * @author Emil Nymark Trangeled - s195478
 * Creates a string for the parameters that does not contain any parameter
 * and stores the error in returnMsg.
 * @param command The command that does not contain any parameters.
 */
void noParameterMsg(char *command){
    char str[100];
    strcat(str, "Command (");
    strcat(str, command);
    strcat(str, ") does not have a parameter!");
    strcpy(returnMsg, str);
}
