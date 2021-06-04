//4.06.2021

#ifndef PEYOT_BOOKREQUEST_H
#define PEYOT_BOOKREQUEST_H


#include "Request.h"
#include "../structures/Date.h"

class BookRequest: public Request {
    std::string keyword;
    std::string login;
    Date date;

public:
    RequestType getType() const {
        return type;
    }

};


#endif //PEYOT_BOOKREQUEST_H
