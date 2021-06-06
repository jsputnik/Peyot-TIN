//21.05.2021

#include "Server.h"
#include "eventLog/ELManager.h"
#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

Server::Server() {
    if ((sock = socket(AF_INET6, SOCK_STREAM, 0)) == -1) {
        cerr << "Socket call error" << endl; //error handler
        exit(1);
    }

    server.sin6_family = AF_INET6;
    inet_pton(AF_INET,"0:0:0:0:0:0:0:1", &(server.sin6_addr));
    server.sin6_addr = in6addr_any;
    //server.sin6_addr = in6addr_any;
    //server.sin6_addr = in6addr_loopback;
    server.sin6_port = htons(45265);

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
    close(sock);
}

void Server::print_server_details() {
    char buf[128];
    inet_ntop(AF_INET, &(server.sin6_addr), buf, sizeof(buf));
    cout<< "Server address: " << buf << endl;
    //cout << "Server IP: " << inet_pton(AF_INET6,(struct in6_addr) server.sin6_addr, buf) << endl;
    cout << "Server port: " << ntohs(server.sin6_port) << endl;
}

void Server::log_server_details() {
    string data;
    //data = "Server IP: " + (string)inet_ntoa((struct in6_addr) server.sin6_addr) + "\n";
    ELManager elManager("../server/eventLog/logs");
    elManager.save(data);
    elManager.close();
}