//4.06.2021

#ifndef PEYOT_LOGINREQUEST_H
#define PEYOT_LOGINREQUEST_H


#include "../structures/User.h"
#include "Request.h"
#include <iostream>

class LoginRequest: public Request {
    std::string keyword;
    std::string login;
    std::string password;

public:
    LoginRequest(std::string keyword, std::string login, std::string password): keyword(keyword), login(login), password(password) {
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

    const std::string &getLogin() const {
        return login;
    }

    void setLogin(const std::string &login) {
        LoginRequest::login = login;
    }

    const std::string &getPassword() const {
        return password;
    }

    void setPassword(const std::string &password) {
        LoginRequest::password = password;
    }

};


#endif //PEYOT_LOGINREQUEST_H
