#include <stdio.h>
#include <stdlib.h>
#include "parse.h"

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

    while (fgets(buffer, 255, (FILE*)fp) != NULL) {
        initBuffer(buffer);
    }

    return 0;
}
