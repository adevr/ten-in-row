//
// Created by ubuntu on 07/12/20.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "helpers.h"

// TODO
// * Libertar todos os nós no final(elementos da lista e depois a lista em si)
Array splitString(char *string, char *dividerChar){
    Array splitedString;

    char *element = strtok(strdup(string), dividerChar);

    splitedString.array = malloc(strlen(element) * sizeof(char));
    splitedString.length = 0;

    while (element != NULL) {
        if(splitedString.length != 0) {
            int sizeOfElement = strlen(element)*sizeof(char);

            if (realloc(splitedString.array,sizeOfElement + sizeof(splitedString.array)) == NULL) {
                perror("Array creation: Error allocating memory");
                exit(0);
            }
        }

        splitedString.array[splitedString.length] = element;
        element = strtok(NULL, dividerChar);
        splitedString.length++;
    }

    return splitedString;
}