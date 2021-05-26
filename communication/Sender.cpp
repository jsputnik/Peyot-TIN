//21.05.2021

#include "Sender.h"
#include <iostream>
#include <cstring>
#include <netinet/in.h>

using namespace std;

Sender::Sender() {
    this->sock = -1;
    this->msg = "";
}

Sender::Sender(int sock, const char* msg) {
    this->sock = sock;
    this->msg = msg;
}

void Sender::send_msg() {
    unsigned int bytes_sent;
    cout << "Sizeof msg to be sent: " << strlen(msg) << endl;
    if ((bytes_sent = send(sock, msg, strlen(msg), 0)) == -1) {
        cerr << "Send error, bytes sent: " << bytes_sent << endl;
        exit(3);
    }
    cout << "Message sent. Bytes sent: " << bytes_sent << endl;
}
