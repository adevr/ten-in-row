//
// Created by ubuntu on 08/12/20.
//

#ifndef TEN_IN_ROW_COMMUNICATION_H
#define TEN_IN_ROW_COMMUNICATION_H

#endif //TEN_IN_ROW_COMMUNICATION_H

enum COMMUNICATION_PROTOTYPE_ENUM {
    PROCESS_ID,
    MESSAGE_CODE,
    MESSAGE
};

enum MESSAGE_CODE_TYPES {
    INFO,
    GAME_MOVE,
    COMMAND,
    REQUEST_QUIT,
    INVALID_USERNAME,
    CONNECTION_REQUEST,
    CONNECTION_ACCEPTED,
    CONNECTION_REFUSED
};

char *initMessageModel(int PID, int messageCode, char *message);

void listeningResponse(int descriptor, char *buffer);
void sendMessage(int destDescriptor, char *message);