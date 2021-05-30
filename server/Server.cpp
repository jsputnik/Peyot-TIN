//21.05.2021

#include "Server.h"
#include "eventLog/ELManager.h"
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

Server::Server() {
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        cerr << "Socket call error" << endl; //error handler
        exit(1);
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); //deprecated
    server.sin_port = htons(45265);
    if (bind(sock, (struct sockaddr *) &server, sizeof server) != 0) {
        cerr << "Bind call error" << endl; //error handler
        exit(2);
    }
}

void Server::start() {
    if (listen(sock, backlog) != 0) {
        cerr << "Listen call error" << endl;
        exit(3);
    }
    while (true) {
       // if (client_sock = accept)
        handler.make_connection(sock);
    }
}

void Server::stop() {
    cout << "here" << endl;
    close(sock);
}

void Server::print_server_details() {
    cout << "Server IP: " << inet_ntoa((struct in_addr) server.sin_addr) << endl;
    cout << "Server port: " << ntohs(server.sin_port) << endl;
}

void Server::log_server_details() {
    string data;
    data = "Server IP: " + (string)inet_ntoa((struct in_addr) server.sin_addr) + "\n";
    ELManager elManager("../server/eventLog/logs");
    elManager.save(data);
    elManager.close();
}