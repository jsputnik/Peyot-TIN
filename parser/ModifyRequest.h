//Peyot
//Iwo Sokal
//4.06.2021

#ifndef PEYOT_MODIFYREQUEST_H
#define PEYOT_MODIFYREQUEST_H


#include "Request.h"
#include "../structures/Date.h"

class ModifyRequest: public Request {
    std::string keyword;
    std::string login;
    std::string old_date;
    std::string new_date;

public:
    ModifyRequest(const std::string &keyword, const std::string &login, const std::string &old_date, const std::string &new_date) : keyword(keyword),
                                                                                            login(login), old_date(old_date), new_date(new_date) {
        type = RequestType::MODIFY;
    }

    RequestType getType() const {
        return type;
    }

    const std::string &getLogin() const {
        return login;
    }

    void setLogin(const std::string &login) {
        ModifyRequest::login = login;
    }

    const std::string &getOldDate() const {
        return old_date;
    }

    void setOldDate(const std::string &oldDate) {
        old_date = oldDate;
    }

    const std::string &getNewDate() const {
        return new_date;
    }

    void setNewDate(const std::string &newDate) {
        new_date = newDate;
    }
};


#endif //PEYOT_MODIFYREQUEST_H
