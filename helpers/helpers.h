//
// Created by ubuntu on 07/12/20.
//

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

