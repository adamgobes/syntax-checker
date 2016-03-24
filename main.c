#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parse.h"
#include "syntax.h"

char *errorString(char *inputLine, char *offence) {
    char *copy = malloc(strlen(inputLine));
    strcpy(copy, inputLine);
    int lengthBeforeError = strlen(inputLine) - strlen(strstr(copy, offence));
    char *upToError = malloc(lengthBeforeError);
    strncpy(upToError, copy, lengthBeforeError);
    char *errorString = malloc(strlen(inputLine) + 3);
    char *asterix = malloc(strlen(offence) + 3);
    strcat(asterix, "***");
    offence = strcat(asterix, offence);
    free(asterix);
    strncpy(errorString, inputLine, strlen(upToError));
    errorString[strlen(inputLine)] = '\0';
    strcat(errorString, offence);
    strcat(errorString, inputLine+lengthBeforeError+strlen(offence)-3);
    return errorString;
}

int main(int argc, char const *argv[]) {
    char file_name[25], inputLine[255];
    FILE *fp;

    printf("Enter the name of file you wish to check\n");
    gets(file_name);

    fp = fopen(file_name, "r"); // read mode

    if (fp == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }


    int fileLine = 0;
    while (fgets(inputLine, 255, (FILE*)fp) != NULL) {
        initBuffer(inputLine);
        fileLine++;
        while (hasNextToken()) {
            char *next = strtok(nextToken(), "\n");
            if (isValidCommand(next)) {
                if (hasNextToken()) {
                    printf("Error at line %d: Only one command per line\n", fileLine);
                }
            } else if (isValidExpression(next)) {
                if (strcmp(next, "SAY") == 0) {
                    /* add logic to make sure token after is wrapped in quotes */
                    char *afterSay = strtok(nextToken(), "\n");
                    if (afterSay[0] != '"' || afterSay[strlen(afterSay)-1] != '"') {
                        printf("Error at line %d: message must be in quotes\n" ,fileLine);
                    }
                } else if (strcmp(next, "REPEAT") == 0) {
                    /* add logic to make sure expression is a valid for loop */
                    char *digits = strtok(nextToken(), "\n");
                    for (int i = 0; i < strlen(digits); i++) {
                        if (!isdigit(digits[i])) {
                            printf("Error at line %d: REPEAT must be followed by a number\n", fileLine);
                            break;
                        }
                    }

                } else if (strcmp(next, "WHILE") == 0) {
                    /* add logic to make sure expression is valid while loop */
                }
            }

            else {
                /* start logic for finding offence */
                break;
            }
        }
    }

    return 0;
}
