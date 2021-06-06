//21.05.2021

#include "Client.h"
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

Client::Client(const char* server_address, const char* server_port) {
//    if ((sock = socket(AF_INET6, SOCK_STREAM, 0)) == -1) {
//        cerr << "Socket call error" << endl;
//        exit(1);
//    }
//    cout << "Socket descriptor: " << sock << endl;

    strcpy(server, server_address);

    memset(&hints, 0x00, sizeof(hints));
    hints.ai_flags = AI_NUMERICSERV;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    rc = inet_pton(AF_INET, server, &serveraddr);
    if(rc == 1){
        hints.ai_family = AF_INET;
        hints.ai_flags |= AI_NUMERICHOST;
    }
    else{
        rc = inet_pton(AF_INET6, server, &serveraddr);
        if(rc == 1){
            hints.ai_family = AF_INET6;
            hints.ai_flags |= AI_NUMERICHOST;
        }
    }

    rc = getaddrinfo(server, server_port, &hints, &res);
    if(rc != 0){
        cerr << "Host not found" << endl;
       exit(1);
    }

    sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if (sock == -1) {
        cerr << "Socket call error" << endl;
        exit(2);
    }

    //server.sin6_family = AF_INET6;
    //server.sin6_addr =
    //server.sin6_addr.s_addr = inet_addr(server_address);
    //server.sin6_port = htons(atoi(server_port));
}

void Client::connect_to_server() {
    if (connect(sock, res->ai_addr, res->ai_addrlen) != 0) {
        cerr << "Connect call error" << endl;
        exit(3);
    }
    cout << "Connected" << endl;
}

void Client::send(const char* msg) {
    sender.set_sock(sock);
    sender.set_msg(msg);
    sender.send_msg();
}

string Client::receive() {
    receiver.set_sock(sock);
    return receiver.receive();
}

void Client::stop(int status_code) {
    send("quit");
    if (status_code != 0) {
        cerr << "Finished forcefully" << endl;
    }
    close(sock);
}

void Client::print_server_details() {
    //cout << "Server IP: " << inet_ntoa((struct in_addr) server.sin_addr) << endl;
    //cout << "Server port: " << ntohs(server.sin_port) << endl;
}
