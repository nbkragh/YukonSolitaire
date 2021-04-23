//
// Created by Emil Trangeled on 15-04-2021.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "CardFunctions.h"

int displayGame(void) {

    char input[25] ="",commands[25]="",parameter[25]="", lastCommand[25] = "", returnMsg[50] = "OK";
    int i;
    char *command[2];


    // while loop for the command loop
    while (strcmp(input, "QQ") != 0) {
        // iterator for command pointer array.
        i = 0;
        // printing the command
        printf("LAST Command: %s\n", lastCommand);
        // printing the error message or just OK if everything went ok.
        printf("Message: %s\n", returnMsg);
        // Printing the input field
        printf("INPUT >");
        //Scanning for a string
        scanf("%[^\n]%*c", input);

        // copies the input to the last command for it
        // to be displayed in the next iteration of the while loop
        strcpy(lastCommand, input);

        //
        char *ptr = strtok(input," ");
        //char *command[2];

        while (ptr){
            command[i++] = ptr;
            ptr = strtok(NULL, " ");
        }
        strcpy(commands, command[0]);
        strcpy(parameter, command[1]);


        for(int j = 0; commands[j]; j++){
            commands[j] = toupper(commands[j]);
        }



        if (strcmp(commands, "LD") == 0){
            printf("LOADING CARDS FROM: %s\n\n", parameter);
            strcpy(returnMsg, "OK");
        }
        else if (strcmp(commands, "SW") == 0){
            if (strcmp(parameter,"") == 0){
                printf("SHOWING CARDS\n\n");
                strcpy(returnMsg, "OK");
            } else {
                strcpy(returnMsg, "Command (SW) does not have a parameter!");
                command[1] = "";
            }

        }
        else if (strcmp(commands, "SL") == 0){
            printf("SPLITTING CARDS FROM: %s\n\n", parameter);
            strcpy(returnMsg, "OK");
        }
        else{
            strcpy(returnMsg,"COMMAND NOT FOUND");
        }

    }
    return 0;
}
