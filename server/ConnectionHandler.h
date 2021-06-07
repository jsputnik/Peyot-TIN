//Peyot
//Iwo Sokal
//21.05.2021

#ifndef PEYOT_CONNECTIONHANDLER_H
#define PEYOT_CONNECTIONHANDLER_H

#include "../communication/Sender.h"
#include "../communication/Receiver.h"


class ConnectionHandler {
    int client_sock;
    unsigned long long clients = 0;
public:
    void make_connection(int server_sock);
    static void* handle_connection(void* args);
    void disconnect();
};


#endif //PEYOT_CONNECTIONHANDLER_H
