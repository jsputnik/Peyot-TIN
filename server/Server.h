//Peyot
//Iwo Sokal, Szymon Kisiel, Olgierd Sobieraj, Illia Yatskevich
//21.05.2021

#ifndef PEYOT_SERVER_H
#define PEYOT_SERVER_H

#include <netinet/in.h>
#include "ConnectionHandler.h"


class Server {
    ConnectionHandler handler;
    int sock;
    struct sockaddr_in server;
    int backlog = 32;
public:
    Server(std::string ip_address);
    void start();
    void stop();
    void print_server_details();
    void log_server_details();
};


#endif //PEYOT_SERVER_H
