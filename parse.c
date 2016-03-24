#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"
typedef int BOOLEAN;


char *buffer;
int bufferSize;

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
    bufferSize = 1;
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
    char *copy = malloc(bufferSize);
    strcpy(copy, buffer);
    char *next = strtok(copy, " ");
    buffer = removeToken(next, buffer);
    bufferSize--;
    return next;
}
