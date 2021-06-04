//4.06.2021

#ifndef PEYOT_CHECKTERMINSBYINSTRUCTORREQUEST_H
#define PEYOT_CHECKTERMINSBYINSTRUCTORREQUEST_H


#include "Request.h"

class CheckTerminsByInstructorRequest: public Request {
    std::string keyword;
    std::string flag;
    std::string login;

public:
    RequestType getType() const {
        return type;
    }
};


#endif //PEYOT_CHECKTERMINSBYINSTRUCTORREQUEST_H
