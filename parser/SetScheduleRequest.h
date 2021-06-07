//Peyot
//Iwo Sokal
//6.06.2021

#ifndef PEYOT_SETSCHEDULEREQUEST_H
#define PEYOT_SETSCHEDULEREQUEST_H

#include "Request.h"


class SetScheduleRequest: public Request {
    std::string keyword;
    std::string date;

public:
    SetScheduleRequest(std::string keyword, std::string date): keyword(keyword), date(date) {
        this->type = RequestType::SETSCHEDULE;
    }

    const std::string &getKeyword() const {
        return keyword;
    }

    void setKeyword(const std::string &keyword) {
        SetScheduleRequest::keyword = keyword;
    }

    const std::string &getDate() const {
        return date;
    }

    void setDate(const std::string &date) {
        SetScheduleRequest::date = date;
    }
};


#endif //PEYOT_SETSCHEDULEREQUEST_H
