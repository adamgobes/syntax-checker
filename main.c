#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parse.h"
#include "syntax.h"

void upperString(char *word) {
    for (int i = 0; i < strlen(word); i++) {
        if (word[i] >= 'a' && word[i] <= 'z')
            word[i] = toupper(word[i]);
    }
}

char *errorString(char *inputLine, char *offence) {
    int oneLine = 0;
    if (strcmp(inputLine, offence) == 0) {
        oneLine = 1;
    }
    char *copy = malloc(strlen(inputLine));
    strcpy(copy, inputLine);
    int lengthAfterError = strlen(strstr(copy, offence));
    int lengthBeforeError = strlen(inputLine) - lengthAfterError;
    char *upToError = malloc(lengthBeforeError);
    upToError[lengthBeforeError] = '\0';
    strncpy(upToError, copy, lengthBeforeError);
    char *asterix = malloc(strlen(offence) + 3);
    strcat(asterix, "***");
    offence = strcat(asterix, offence);
    free(asterix);
    if (oneLine) {
        return offence;
    }
    char *errorString = malloc(strlen(inputLine) + 3);
    strncpy(errorString, inputLine, strlen(upToError));
    errorString[strlen(inputLine)] = '\0';
    strcat(errorString, offence);
    strcat(errorString, inputLine+lengthBeforeError+strlen(offence)-3);
    printf("%s\n", errorString);
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
        upperString(inputLine);
        initBuffer(inputLine);
        fileLine++;
        while (hasNextToken()) {
            char *next = strtok(nextToken(), "\n");
            if (isValidCommand(next)) {
                if (hasNextToken()) {
                    printf("Error at line %d: Only one command per line\n", fileLine);
                    break;
                }
            } else if (isValidExpression(next)) {
                if (strcmp(next, "SAY") == 0) {
                    /* add logic to make sure token after is wrapped in quotes */
                    char *afterSay = strtok(nextToken(), "\n");
                    if (afterSay[0] != '"' || afterSay[strlen(afterSay)-1] != '"') {
                        printf("Error at line %d: message must be in quotes\n" ,fileLine);
                        break;
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
                    char *times = strtok(nextToken(), "\n");
                    if (strcmp(times, "TIMES") != 0) {
                        printf("Error at line %d: REPEAT expression must contain TIMES\n", fileLine);
                        break;
                    }

                    while (hasNextToken()) {
                        char *command = strtok(nextToken(), ",");
                        command = strtok(command, "\n");
                        if (!isValidCommand(command)) {
                            printf("Error at line %d: REPEAT expression must contain valid commands\n", fileLine);
                        }
                    }

                } else if (strcmp(next, "WHILE") == 0) {
                    /* add logic to make sure expression is valid while loop */
                    char *not = strtok(nextToken(), "\n");
                    if (strcmp(not, "NOT") != 0) {
                        printf("Error at line %d: WHILE must be followed by NOT\n", fileLine);
                        break;
                    }

                    char *c = strtok(nextToken(), "\n");
                    if (strcmp(c, "DETECTMARKER") != 0) {
                        printf("Error at line %d: WHILE must contain boolean DETECTMARKER\n", fileLine);
                        break;
                    }

                    char *doStatement = strtok(nextToken(), "\n");
                    if (strcmp(doStatement, "DO") != 0) {
                        printf("Error at line %d: WHILE must contain DO\n", fileLine);
                        break;
                    }

                    while (hasNextToken()) {
                        char *command = strtok(nextToken(), ",");
                        command = strtok(command, "\n");
                        if (!isValidCommand(command)) {
                            printf("Error at line %d: WHILE expression must contain valid commands\n", fileLine);
                            break;
                        }
                    }

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
