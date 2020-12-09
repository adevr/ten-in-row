//
// Created by ubuntu on 08/12/20.
//
#include <string.h>
#include <stdio.h>
#include "../../helpers/helpers.h"
#include "../../constants/constants.h"

#include "Communication.h"

char *getStringToSend(int PID, int error, int messageCode, char *message) {
    char *string;

    strcat(string, getNumberInString(PID));
    strcat(string, DIVIDER_CHAR);
    strcat(string, getNumberInString(error));
    strcat(string, DIVIDER_CHAR);
    strcat(string, getNumberInString(messageCode));
    strcat(string, DIVIDER_CHAR);
    strcat(string, message);

    return string;
}