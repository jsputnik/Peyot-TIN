//4.06.2021

#ifndef PEYOT_RESIGNREQUEST_H
#define PEYOT_RESIGNREQUEST_H


#include "Request.h"
#include "../structures/Date.h"

class ResignRequest: public Request {
    std::string keyword;
    std::string login;
    Date date;

public:
    RequestType getType() const {
        return type;
    }

    ResignRequest(const std::string &keyword, const std::string &login, const Date &date) : keyword(keyword),
                                                                                            login(login), date(date) {}

    const std::string &getKeyword1() const {
        return keyword;
    }

    void setKeyword1(const std::string &keyword) {
        ResignRequest::keyword = keyword;
    }

    const std::string &getLogin() const {
        return login;
    }

    void setLogin(const std::string &login) {
        ResignRequest::login = login;
    }

    const Date &getDate() const {
        return date;
    }

    void setDate(const Date &date) {
        ResignRequest::date = date;
    }

};


#endif //PEYOT_RESIGNREQUEST_H
