//4.06.2021

#ifndef PEYOT_BOOKREQUEST_H
#define PEYOT_BOOKREQUEST_H


#include "Request.h"
#include "../structures/Date.h"

class BookRequest: public Request {
    std::string keyword;
    std::string login;
    std::string date;

public:
    BookRequest(const std::string &keyword, const std::string &login, const std::string &date) : keyword(keyword),
                                                                                                       login(login),
                                                                                                       date(date) {
        type = RequestType::BOOK;
    }

    RequestType getType() const {
        return type;
    }

    const std::string &getKeyword() const {
        return keyword;
    }

    void setKeyword(const std::string &keyword) {
        BookRequest::keyword = keyword;
    }

    const std::string &getLogin() const {
        return login;
    }

    void setLogin(const std::string &login) {
        BookRequest::login = login;
    }

};


#endif //PEYOT_BOOKREQUEST_H
