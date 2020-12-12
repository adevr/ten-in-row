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
    GAME_MOVE,
    COMMAND,
    CONNECTION_REQUEST,
    CONNECTION_REFUSED
};

char *initMessageModel(int PID, int messageCode, char *message);

void listeningResponse(int descriptor, char *buffer);
void sendMessage(int destDescriptor, char *message);