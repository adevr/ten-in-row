//
// Created by ubuntu on 08/12/20.
//

#ifndef TEN_IN_ROW_COMMUNICATION_H
#define TEN_IN_ROW_COMMUNICATION_H

#endif //TEN_IN_ROW_COMMUNICATION_H

enum MESSAGE_CODE_TYPES {
    GAME_MOVE,
    COMMAND
};

enum COMMUNICATION_PROTOTYPE_ENUM {
    PROCESS_ID,
    ERROR,
    MESSAGE_CODE,
    MESSAGE
};

char *getStringToSend(int PID, int error, int messageCode, char *message);