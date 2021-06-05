//4.06.2021

#ifndef PEYOT_MODIFYREQUEST_H
#define PEYOT_MODIFYREQUEST_H


#include "Request.h"
#include "../structures/Date.h"

class ModifyRequest: public Request {
    std::string keyword;
    std::string login;
    Date old_date;
    Date new_date;

public:
    RequestType getType() const {
        return type;
    }
};


#endif //PEYOT_MODIFYREQUEST_H
