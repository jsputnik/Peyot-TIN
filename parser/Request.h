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

    virtual const std::string &getLogin() const {
        return "";
    }

    virtual void setLogin(const std::string &login) {
        ;
    }

    virtual const std::string &getPassword() const {
        return "";
    }

    virtual void setPassword(const std::string &password) {
        ;
    }

    std::string rtype_to_string();
};


#endif //PEYOT_REQUEST_H
