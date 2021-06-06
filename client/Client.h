//21.05.2021

#ifndef PEYOT_CLIENT_H
#define PEYOT_CLIENT_H

#include <netinet/in.h>
#include <netdb.h>
#include "../communication/Sender.h"
#include "../communication/Receiver.h"

class Client {
    static const int SERVER_SIZE = 128;

    Sender sender;
    Receiver receiver;
    int sock;
    char server[SERVER_SIZE];
    struct in6_addr serveraddr;
    struct addrinfo hints;
    struct addrinfo *res = NULL;
    int rc;

    //struct sockaddr_in6 server;
public:
    Client(const char* server_address, const char* server_port);
    void connect_to_server();
    void send(const char* msg);
    std::string receive();
    void stop(int status_code);
    void print_server_details();
    bool isResponseValid(std::string response); //handled in receiver/sender/other class
};


#endif //PEYOT_CLIENT_H
