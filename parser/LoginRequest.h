//4.06.2021

#ifndef PEYOT_LOGINREQUEST_H
#define PEYOT_LOGINREQUEST_H


#include "../structures/User.h"
#include "Request.h"
#include <iostream>

class LoginRequest: public Request {
    std::string keyword;
    User user;

public:
    LoginRequest(std::string keyword, User user): keyword(keyword), user(user) {
        type = RequestType::LOGIN;
    }

    RequestType getType() const {
        return type;
    }

    const std::string &getKeyword() const {
        return keyword;
    }

    void setKeyword(const std::string &keyword) {
        this->keyword = keyword;
    }

    const User &getUser() const {
        return user;
    }

    void setUser(const User &user) {
        this->user = user;
    }

};


#endif //PEYOT_LOGINREQUEST_H
