//21.05.2021

#include "ConnectionHandler.h"
#include "security/SecurityManager.h"
#include <pthread.h>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <openssl/sha.h>

using namespace std;

void* ConnectionHandler::handle_connection(void* args) {
    cout << "Handle connection..." << endl;
    int sock = *(int*)args;
    Receiver receiver(sock);
    SecurityManager sm;
    string msg_rcvd;
    while(msg_rcvd != "quit") {
        //execute request
        //database manager
        //logger
        msg_rcvd = receiver.receive();
        //comment block below only temporarily
        int salt_length = 16;
        int encoded_salt_length = 4*(salt_length+2)/3;
        unsigned char salt[encoded_salt_length];
        sm.generate_salt(salt, encoded_salt_length);
        cout << "Encoded salt: " << endl;
        for (unsigned int i = 0; i < encoded_salt_length; ++i) {
            cout << salt[i];
        }
        cout << endl;
        unsigned char hash[SHA512_DIGEST_LENGTH];
        unsigned char encoded[4*(SHA512_DIGEST_LENGTH+2)/3];
        sm.hash_password(SecurityManager::merge_salt_with_password(salt, salt_length, msg_rcvd), hash, encoded, SHA512_DIGEST_LENGTH);
        const char* msg = "Answer 123";
        Sender sender(sock, msg); //TODO (?): move above while loop later
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
