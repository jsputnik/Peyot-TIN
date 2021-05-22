//21.05.2021

#ifndef PEYOT_RECEIVER_H
#define PEYOT_RECEIVER_H

#include <string>


class Receiver {
    int sock;
    static unsigned int buf_size;
    char buf[2048];
public:
    Receiver();
    Receiver(int sock);
    std::string receive();
    void set_sock(int sock) {this->sock = sock;}
};


#endif //PEYOT_RECEIVER_H
