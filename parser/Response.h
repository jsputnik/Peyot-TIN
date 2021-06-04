//4.06.2021

#ifndef PEYOT_RESPONSE_H
#define PEYOT_RESPONSE_H

#include <string>

class Response {
    int status_code;
    std::string message;
    std::string data; //no need to check if valid ?

};


#endif //PEYOT_RESPONSE_H
