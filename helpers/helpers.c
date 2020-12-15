/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "helpers.h"
#include "../constants/constants.h"

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

long stringToNumber(char *string) {
    char *pChar;
    return strtol(string, &pChar,10);
}

void freeTheArrayAllocatedMemory(Array *array) {
    //for (int i = 0; i < array->length; i++) {
    //    free(*(array->array + i));
    //}
    free(array->array);
    array->length = 0;
}