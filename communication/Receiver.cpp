//21.05.2021

#include "Receiver.h"
#include <iostream>
#include <sys/socket.h>
#include <cstring>

using namespace std;

Receiver::Receiver() {
    this->sock = -1;
}

Receiver::Receiver(int sock) {
    this->sock = sock;
}

string Receiver::receive() {
    unsigned int bytes_rcvd;
    if ((bytes_rcvd = recv(sock, buf, buf_size, 0))  == -1) {
        cerr << "Accept call error, bytes received: " << bytes_rcvd << endl;
        exit(5);
    }
    string msg = buf;
    memset(buf, 0, sizeof buf); //clear buffer
    return msg;
}
