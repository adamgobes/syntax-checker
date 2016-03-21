#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"
typedef int BOOLEAN;


char *buffer;
int bufferSize = 1;

char* removeToken(char* substring, char* string) {
    int len = strlen(substring);
    if (bufferSize == 1) {
        string += len;
    } else {
        string += len+1;
    }
    return string;
}

void initBuffer(char *inputLine) {
    buffer = inputLine;
    int len = strlen(buffer);
    for(int i=0; i <= len; i++) {
        if(buffer[i] == ' ')
            bufferSize++;
    }
}


BOOLEAN hasNextToken() {
    if (bufferSize != 0)
        return 1;
    return 0;
}

char *nextToken() {
    char *next = strtok(buffer, " ");
    buffer = removeToken(next, buffer);
    bufferSize--;
    return next;
}
