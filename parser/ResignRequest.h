//Peyot
//Iwo Sokal, Illia Yatskevich
//4.06.2021

#ifndef PEYOT_RESIGNREQUEST_H
#define PEYOT_RESIGNREQUEST_H


#include "Request.h"
#include "../structures/Date.h"

class ResignRequest: public Request {
    std::string keyword;
    std::string login;
    std::string date;

public:
    RequestType getType() const {
        return type;
    }

    ResignRequest(const std::string &keyword, const std::string &login, const std::string &date) : keyword(keyword),
                                                                                            login(login), date(date) {
        type = RequestType::RESIGN;
    }

    const std::string &getKeyword() const {
        return keyword;
    }

    void setKeyword(const std::string &keyword) {
        ResignRequest::keyword = keyword;
    }

    const std::string &getLogin() const {
        return login;
    }

    void setLogin(const std::string &login) {
        ResignRequest::login = login;
    }

    const std::string &getDate() const {
        return date;
    }

    void setDate(const std::string &Date) {
        date = Date;
    }

};


#endif //PEYOT_RESIGNREQUEST_H
