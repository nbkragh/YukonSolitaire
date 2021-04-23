//
// Created by Emil Trangeled on 15-04-2021.
//

#include <stdio.h>
#include <string.h>
#include "CardFunctions.h"

int displayGame(void) {

    char input[25] ="",commands[25]="",parameter[25]="", lastCommand[25] = "", returnMsg[25] = "OK";
    int i = 0;
    char *command[2];

    // while loop for the command loop
    while (strcmp(input, "QQ") != 0) {
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
        strcpy(command, command[0]);
        strcpy(parameter, command[1]);
//
//        for (int i = 0; i < 2; ++i) {
//            printf("%s\n", command[i]);
//        }



        if (strcmp(command[0], "LD") == 0){
            printf("LOADING CARDS FROM: %s\n\n", command[1]);
            strcpy(returnMsg, "OK");
        }
        else if (strcmp(command[0], "SW") ==0){
            printf("SHOWING CARDS\n\n");
            strcpy(returnMsg, "OK");
        }
        else if (strcmp(command[0], "SL") == 0){
            printf("SPLITTING CARDS FROM: %s\n\n", command[1]);
            strcpy(returnMsg, "OK");
        }
        else{
            //printf("COMMAND NOT FOUND\n");
            strcpy(returnMsg,"COMMAND NOT FOUND");
            //printf("\n");
        }

    }
    return 0;
}
