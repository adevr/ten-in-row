/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>

#include "helpers.h"
#include "../constants/constants.h"

Array splitString(char *string)
{
    Array splitedString;

    char *element = strtok(string, DIVIDER_CHAR);

    splitedString.array = malloc(strlen(element) * sizeof(char));
    splitedString.length = 0;

    while (element != NULL)
    {
        if (splitedString.length != 0)
        {
            int sizeOfElement = strlen(element) * sizeof(char);

            if (realloc(splitedString.array, sizeof(splitedString.array) + sizeOfElement) == NULL)
            {
                perror("A criar o array: Erro ao alocar memoria");
                exit(0);
            }
        }

        splitedString.array[splitedString.length] = element;
        element = strtok(NULL, DIVIDER_CHAR);
        splitedString.length++;
    }

    return splitedString;
}

int getNumberDigits(int number)
{
    if (number < 10)
        return 1;
    return 1 + getNumberDigits(number / 10);
}

char *getNumberInString(int number)
{
    char pidString[getNumberDigits(number) + 1];
    snprintf(pidString, sizeof(pidString), "%d", number);

    return strdup(pidString);
}

long stringToNumber(char *string)
{
    char *pChar;
    return strtol(string, &pChar, 10);
}

void freeTheArrayAllocatedMemory(Array *array)
{
    //for (int i = 0; i < array->length; i++) {
    //    free(*(array->array + i));
    //}
    free(array->array);
    array->length = 0;
}

void printContent(char *stringToDisplay, int fdToCompare)
{
    if (fdToCompare != -1)
    {
        int stringLength = strlen(stringToDisplay);
        printf("%i", stringLength);
        fflush(stdout);
    }

    printf("%s", stringToDisplay);
    fflush(stdout);
}

void initRandom()
{
    srand(time(NULL));
}

int intUniformRnd(int min, int max)
{
    return min + rand() % (max - min + 1);
}