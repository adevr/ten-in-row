/**
 * Alexandre Reis - 2018019414
 * Diogo Barbosa - 2018012425
 */

#include <string.h>
#include <stdio.h>
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
}

void sendMessage(int fileDescriptor, char *message) {
    int messageLength = strlen(message);

    write(fileDescriptor, &messageLength, sizeof(int));
    write(fileDescriptor, message, messageLength);
}

void sendMessageToChildProcess(int writeFileDescriptor, char *message) {
    char *auxMessage = strdup(message);
    
    strcat(auxMessage, "\n");

    int messageLength = strlen(auxMessage);

    write(writeFileDescriptor, auxMessage, messageLength);

}

void communicateWithChildProcess(int writeFileDescriptor, int readFileDescriptor, char *messageToSend, char *responseBuffer) {
    int messageLength = 0;
    char messageLengthBuffer[STRING_BUFFER] = "\0";

    sendMessageToChildProcess(writeFileDescriptor, messageToSend);
    read(readFileDescriptor, messageLengthBuffer, sizeof(int));
    
    messageLength = stringToNumber(messageLengthBuffer);
    read(readFileDescriptor, responseBuffer, messageLength);
}