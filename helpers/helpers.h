//
// Created by ubuntu on 07/12/20.
//

#ifndef TEN_IN_ROW_HELPERS_H
#define TEN_IN_ROW_HELPERS_H

#endif

typedef struct Array {
    void **array;
    int length;
} Array;


Array splitString(char *string, char *dividerChar);

void freeTheArrayAllocatedMemory(Array *array);