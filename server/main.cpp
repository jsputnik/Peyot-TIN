//13.05.2021
#include <iostream>
#include "Server.h"

using namespace std;

int main() {
    std::cout << "Start server" << std::endl;
    Server server;
    server.print_server_details();
    server.start();
    server.stop();
    return 0;
}

//const unsigned int NUM_THREADS = 5;
//
//void* test(void* args) {
//    cout << "Watek " << *(int*)args << endl;
//}
//
//void* handle_connection(void* args) {
//    unsigned int buf_size = 2048;
//    char buf[buf_size];
//    int client_sock = *(int*)args;
//    cout << "Handle connection..." << endl;
//    unsigned int bytes_rcvd;
//    if ((bytes_rcvd = recv(client_sock, buf, buf_size, 0))  == -1) {
//        cerr << "Accept call error, bytes received: " << bytes_rcvd << endl;
//        exit(5);
//    }
//    cout << "Bytes received: " << bytes_rcvd << endl;
//    cout << "Message received: " << buf << endl;
//    unsigned int bytes_sent;
//    const char* msg = "Answer 123";
//    cout << "sizeof msg: " << strlen(msg) << endl;
//    if ((bytes_sent = send(client_sock, msg, strlen(msg), 0)) == -1) {
//        cerr << "Accept call error, bytes sent: " << bytes_sent << endl;
//        exit(3);
//    }
//    cout << "Bytes sent: " << bytes_sent << endl;
//    cout << "Connection finished" << endl;
//    close(client_sock);
//}
//int main() {
////    pthread_t threads[NUM_THREADS]; //threads ids table
////    int thread_args[NUM_THREADS]; //threads values
////    for (int i = 0; i < NUM_THREADS; ++i) {
////        thread_args[i] = i;
////        pthread_create(&threads[i], nullptr, test, &thread_args[i]);
////    }
////
////    for (unsigned long thread : threads) {
////        pthread_join(thread, nullptr);
////    }
//
//    std::cout << "Start server" << std::endl;
////    Server server;
//    int sock, client_sock;
//    struct sockaddr_in server{};
//    int backlog = 32; //max number of connections to be queued in socket
//    unsigned int buf_size = 2048;
//    char buf[buf_size];
//
//    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
//        cerr << "Socket call error" << endl;
//        exit(1);
//    }
//    cout << "Socket descriptor: " << sock << endl;
//
//    server.sin_family = AF_INET;
//    //INADDR_ANY is 0.0.0.0, set later (?)
//    server.sin_addr.s_addr = inet_addr("127.0.0.1");//IN_ADDR_ANY;//htonl(INADDR_ANY);
////    server.sin_port = 0;
//    server.sin_port = htons(45265);
//
//   cout << "Server IP: " << inet_ntoa((struct in_addr) server.sin_addr) << endl;
//    if (bind(sock, (struct sockaddr *) &server, sizeof server) != 0) {
//        cerr << "Bind call error" << endl;
//        exit(2);
//    }
//
//    //get server port
//    unsigned int length = sizeof server;
//    if (getsockname(sock,(struct sockaddr *) &server, &length) == -1) {
//        cerr << "Get socket name call error" << endl;
//        exit(3);
//    }
//    cout << "Server port: " << ntohs(server.sin_port) << endl;
//
//    //proc/sys/net/ipv4/tcp_max_syn_backlog = 256
//    if (listen(sock, backlog) != 0) {
//        cerr << "Listen call error" << endl;
//        exit(3);
//    }
//    unsigned long long clients = 0;
//    pthread_t thread_id;
//    while (true) {
//        if ((client_sock = accept(sock, (struct sockaddr*) nullptr, (unsigned int*) nullptr)) == -1) {
//            cerr << "Accept call error on msgsock: " << client_sock << endl;
//        }
//        pthread_create(&thread_id, nullptr, handle_connection, &client_sock);
//        ++clients;
//    }
//
//    close(sock);
//
//    return 0;
//}
