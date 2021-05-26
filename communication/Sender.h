//21.05.2021

#ifndef PEYOT_SENDER_H
#define PEYOT_SENDER_H

class Sender {
    int sock;
    const char* msg;
public:
    Sender();
    Sender(int sock, const char* msg = "");
    void send_msg();
    void set_msg(const char* msg) {this->msg = msg;}
    void set_sock(int sock) {this->sock = sock;}
};


#endif //PEYOT_SENDER_H
