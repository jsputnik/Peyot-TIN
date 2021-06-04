//4.06.2021

#ifndef PEYOT_REQUEST_H
#define PEYOT_REQUEST_H


#include "RequestType.h"
#include "../structures/User.h"
#include <string>

class Request {
protected:
    RequestType type;

public:
    Request();

    virtual RequestType getType() const {
        return type;
    }

    virtual const std::string &getKeyword() const {
        return "";
    }

    virtual void setKeyword(const std::string &keyword) {
        ;
    }

    virtual const User &getUser() const {
        return User("","","");
    }

    virtual void setUser(const User &user) {
        ;
    }

    std::string rtype_to_string();
};


#endif //PEYOT_REQUEST_H
