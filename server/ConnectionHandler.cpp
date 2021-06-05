//21.05.2021

#include "ConnectionHandler.h"
#include "security/SecurityManager.h"
#include "Executor.h"
#include "../parser/Parser.h"
#include <pthread.h>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

void* ConnectionHandler::handle_connection(void* args) {
    cout << "Handle connection..." << endl;
    int sock = *(int*)args;
    Receiver receiver(sock);
    string message;
    while (message != "quit") { //refactor later
        message = receiver.receive();
        Parser p(message);
        Executor executor(p.parse_request());
        executor.execute();
        Sender sender(sock, executor.getResponse().c_str());
        sender.send_msg();
    }
    cout << "Connection finished with client with socked id: " << sock << endl;
    close(sock);
}

void ConnectionHandler::make_connection(int server_sock) {
    pthread_t thread_id;
    if ((client_sock = accept(server_sock, (struct sockaddr *) nullptr, (unsigned int *) nullptr)) == -1) {
        cerr << "Accept call error on msgsock: " << client_sock << endl;
    }
    pthread_create(&thread_id, nullptr, handle_connection, &client_sock);
    ++clients;
}
