#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "syntax.h"

const char *commands[8] = {
    "TAKEASTEP",
    "LEFT",
    "RIGHT",
    "PICKUP",
    "DROP",
    "DETECTMARKER",
    "TURNON",
    "TURNOFF"
};

const char *expressions[6] = {
    "REPEAT",
    "TIMES",
    "WHILE",
    "NOT",
    "DETECTMARKER",
    "SAY"

};

int isValidCommand(char *token) {
    int i;
    for (i = 0; i < 8; i++) {
        if (strcmp(token, commands[i]) == 0)
            return 1;
    }
    return 0;
}

int isValidExpression(char *token) {
    int i;
    for (i = 0; i < 6; i++) {
        if (strcmp(token, expressions[i]) == 0)
            return 1;
    }
    return 0;
}
