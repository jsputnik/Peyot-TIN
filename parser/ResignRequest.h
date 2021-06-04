//4.06.2021

#ifndef PEYOT_RESIGNREQUEST_H
#define PEYOT_RESIGNREQUEST_H


#include "Request.h"
#include "../structures/Date.h"

class ResignRequest: public Request {
    std::string keyword;
    std::string login;
    Date date;

public:
    RequestType getType() const {
        return type;
    }

};


#endif //PEYOT_RESIGNREQUEST_H
