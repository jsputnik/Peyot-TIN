//4.06.2021

#ifndef PEYOT_RESPONSE_H
#define PEYOT_RESPONSE_H

#include <string>

class Response {
    int first;
    int second;
    int third;
    std::string message;

public:
    Response(int first, int second, int third, const std::string &message) : first(
            first), second(second), third(third), message(message) {
    }

};


#endif //PEYOT_RESPONSE_H
