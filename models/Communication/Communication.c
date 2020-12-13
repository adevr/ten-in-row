//
// Created by ubuntu on 08/12/20.
//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../helpers/helpers.h"
#include "../../constants/constants.h"

#include "Communication.h"

char *initMessageModel(int PID, int messageCode, char *message) {
    char string[STRING_BUFFER];
    memset(string, 0, sizeof(string));

    strcpy(string, getNumberInString(PID));
    strcat(string, DIVIDER_CHAR);
    strcat(string, getNumberInString(messageCode));
    strcat(string, DIVIDER_CHAR);
    strcat(string, strdup(message));

    return strdup(string);
}

void listeningResponse(int fileDescriptor, char *buffer) {
    int messageLength = 0;

    read(fileDescriptor, &messageLength, sizeof(int));
    read(fileDescriptor, buffer, messageLength);

    //printf("\n### Listened Message:\n %s\tSize:  %i ###\n", buffer, messageLength);
}

void sendMessage(int fileDescriptor, char *message) {
    int messageLength = strlen(message);

    //printf("\n### Message Writted: %s | Size:  %i ###\n", message, messageLength);

    write(fileDescriptor, &messageLength, sizeof(int));
    write(fileDescriptor, message, messageLength);
}