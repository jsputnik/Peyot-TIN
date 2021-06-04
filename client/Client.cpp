//21.05.2021

#include "Client.h"
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

Client::Client(const char* server_address, const char* server_port) {
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        cerr << "Socket call error" << endl;
        exit(1);
    }
    cout << "Socket descriptor: " << sock << endl;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(server_address);
    server.sin_port = htons(atoi(server_port));
}

void Client::connect_to_server() {
    if (connect(sock, (struct sockaddr*) &server, sizeof server) != 0) {
        cerr << "Connect call error" << endl;
        exit(2);
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
    cout << "Server IP: " << inet_ntoa((struct in_addr) server.sin_addr) << endl;
    cout << "Server port: " << ntohs(server.sin_port) << endl;
}
