//Peyot
//Iwo Sokal, Illia Yatskevich
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

    int getFirst() const {
        return first;
    }

    int getSecond() const {
        return second;
    }

    int getThird() const {
        return third;
    }

    const std::string &getMessage() const {
        return message;
    }

};


#endif //PEYOT_RESPONSE_H
