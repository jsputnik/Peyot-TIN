//13.05.2021
#include <iostream>
#include <string>
#include "Client.h"

using namespace std;

int main() {
   std::cout << "Start client" << std::endl;
   const char* server_address = "127.0.0.1";
   const char* server_port = "45265";
   Client client(server_address, server_port);
   client.print_server_details(); //server IP address and port client is connecting to
   client.connect_to_server();
   string msg = "";
   while (msg != "quit") {
       getline(cin, msg);
       client.send(msg.c_str());
       cout << client.receive() << endl;
   }
   client.stop();


    return 0;
}

//int main() {
//    std::cout << "Start client" << std::endl;
//    const char* server_address = "127.0.0.1";
//    const char* server_port = "45265";
//    unsigned int buf_size = 2048;
//    char buf[buf_size];
//
//    int sock;
//    struct sockaddr_in server;
//
//    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
//        cerr << "Socket call error" << endl;
//        exit(1);
//    }
//    cout << "Socket descriptor: " << sock << endl;
//
//    server.sin_family = AF_INET;
//    server.sin_addr.s_addr = inet_addr(server_address);
//    server.sin_port = htons(atoi(server_port));
//
//    cout << "Server IP: " << inet_ntoa((struct in_addr) server.sin_addr) << endl;
//    cout << "Server port: " << ntohs(server.sin_port) << endl;
//
//    if (connect(sock, (struct sockaddr*) &server, sizeof server) != 0) {
//        cerr << "Connect call error" << endl;
//        exit(2);
//    }
//    cout << "Connected" << endl;
//
//    //
//    unsigned int bytes_sent;
//    const char* msg = "Test 123";
//    cout << "Sleeping....." << endl;
//    sleep(5);
//    if ((bytes_sent = send(sock, msg, strlen(msg), 0)) == -1) {
//        cerr << "Accept call error, bytes sent: " << bytes_sent << endl;
//        exit(3);
//    }
//    cout << "Bytes sent: " << bytes_sent << endl;
//    unsigned int bytes_rcvd;
//    if ((bytes_rcvd = recv(sock, buf, buf_size, 0))  == -1) {
//        cerr << "Accept call error, bytes received: " << bytes_rcvd << endl;
//        exit(4);
//    }
//    cout << "Bytes received: " << bytes_rcvd << endl;
//    cout << "Message received: " << buf << endl;
//
//    close(sock);
//
//    return 0;
//}

