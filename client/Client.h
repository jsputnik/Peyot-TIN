//21.05.2021

#ifndef PEYOT_CLIENT_H
#define PEYOT_CLIENT_H

#include <netinet/in.h>
#include "../communication/Sender.h"
#include "../communication/Receiver.h"

class Client {
    Sender sender;
    Receiver receiver;
    int sock;
    struct sockaddr_in server;
public:
    Client(const char* server_address, const char* server_port);
    void connect_to_server();
    void send(const char* msg);
    std::string receive();
    void stop(int status_code);
    void print_server_details();
};


#endif //PEYOT_CLIENT_H
