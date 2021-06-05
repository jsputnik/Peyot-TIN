//4.06.2021

#ifndef PEYOT_REGISTERREQUEST_H
#define PEYOT_REGISTERREQUEST_H


#include "../structures/User.h"
#include "Request.h"

class RegisterRequest: public Request {
    std::string keyword;
    User user;

public:
    RegisterRequest(std::string keyword, User user): keyword(keyword), user(user) {
        type = RequestType::LOGIN;
    }

    RequestType getType() const {
        return type;
    }

    const std::string &getKeyword() const {
        return keyword;
    }

    void setKeyword(const std::string &keyword) {
        RegisterRequest::keyword = keyword;
    }

    const User &getUser() const {
        return user;
    }

    void setUser(const User &user) {
        RegisterRequest::user = user;
    }

};


#endif //PEYOT_REGISTERREQUEST_H
