//4.06.2021

#ifndef PEYOT_CHECKMYTERMINSREQUEST_H
#define PEYOT_CHECKMYTERMINSREQUEST_H


#include "Request.h"

class CheckMyTerminsRequest: public Request {
    std::string keyword;
    std::string flag;

public:
    RequestType getType() const {
        return type;
    }
};


#endif //PEYOT_CHECKMYTERMINSREQUEST_H
