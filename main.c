#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"
#include "syntax.h"

int main(int argc, char const *argv[]) {
    char file_name[25], buffer[255];
    FILE *fp;

    printf("Enter the name of file you wish to check\n");
    gets(file_name);

    fp = fopen(file_name,"r"); // read mode

    if (fp == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, sizeof(buffer), (FILE*)fp) != NULL) {
        initBuffer(buffer);
        while (hasNextToken()) {
            char *next = nextToken();
            if (isValidCommand(next) || isValidExpression(next)) {
                printf("Valid!\n");
            } else {
                printf("Invalid!\n");
            }
        }

    }

    return 0;
}
