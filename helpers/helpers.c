//
// Created by ubuntu on 07/12/20.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "helpers.h"
#include "../constants/constants.h"

// TODO
// * Libertar todos os nós no final(elementos da lista e depois a lista em si)
Array splitString(char *string){
    Array splitedString;

    char *element = strtok(string, DIVIDER_CHAR);

    splitedString.array = malloc(strlen(element) * sizeof(char));
    splitedString.length = 0;

    while (element != NULL) {
        if(splitedString.length != 0) {
            int sizeOfElement = strlen(element)*sizeof(char);

            if (realloc(splitedString.array,sizeof(splitedString.array) + sizeOfElement) == NULL) {
                perror("Array creation: Error allocating memory");
                exit(0);
            }
        }

        splitedString.array[splitedString.length] = element;
        element = strtok(NULL, DIVIDER_CHAR);
        splitedString.length++;
    }

    return splitedString;
}

int getNumberDigits(int number) {
    if (number < 10) return 1;
    return 1 + getNumberDigits(number / 10);
}

char *getNumberInString(int number) {
    char pidString[getNumberDigits(number) + 1];

    snprintf(pidString, sizeof(pidString),"%d", number);

    return strdup(pidString);
}