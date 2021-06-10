//Peyot
//Iwo Sokal, Illia Yatskevich
//4.06.2021

#ifndef PEYOT_CHECKMYTERMINSREQUEST_H
#define PEYOT_CHECKMYTERMINSREQUEST_H


#include "Request.h"

class CheckMyTerminsRequest: public Request {
    std::string keyword;
    std::string flag;

public:
    RequestType getType() const {
        return type;
    }

    CheckMyTerminsRequest(const std::string &keyword, const std::string &flag) : keyword(keyword), flag(flag) {
        type = RequestType::CHECKMYTERMINS;
    }

    const std::string &getKeyword() const {
        return keyword;
    }

    void setKeyword(const std::string &keyword) {
        CheckMyTerminsRequest::keyword = keyword;
    }

    const std::string &getFlag() const {
        return flag;
    }

    void setFlag(const std::string &flag) {
        CheckMyTerminsRequest::flag = flag;
    }
};


#endif //PEYOT_CHECKMYTERMINSREQUEST_H
