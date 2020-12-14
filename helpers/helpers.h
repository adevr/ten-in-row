/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#ifndef TEN_IN_ROW_HELPERS_H
#define TEN_IN_ROW_HELPERS_H

typedef struct Array {
    char **array;
    int length;
} Array;


Array splitString(char *string);
int getNumberDigits(int number);
char *getNumberInString(int number);
long stringToNumber(char *string);
void freeTheArrayAllocatedMemory(Array *array);

#endif

