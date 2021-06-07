//Peyot
//Iwo Sokal
//4.06.2021

#ifndef PEYOT_REGISTERREQUEST_H
#define PEYOT_REGISTERREQUEST_H


#include "../structures/User.h"
#include "Request.h"

class RegisterRequest: public Request {
    std::string keyword;
    std::string flag;
    std::string login;
    std::string password;

public:
    RegisterRequest(std::string keyword, std::string flag, std::string login, std::string password): keyword(keyword), flag(flag), login(login), password(password) {
        type = RequestType::REGISTER;
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

    const std::string &getFlag() const {
        return flag;
    }

    void setFlag(const std::string &flag) {
        RegisterRequest::flag = flag;
    }

    const std::string &getLogin() const {
        return login;
    }

    void setLogin(const std::string &login) {
        RegisterRequest::login = login;
    }

    const std::string &getPassword() const {
        return password;
    }

    void setPassword(const std::string &password) {
        RegisterRequest::password = password;
    }

};


#endif //PEYOT_REGISTERREQUEST_H
