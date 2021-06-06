//6.06.2021

#ifndef PEYOT_CHECKINSTRUCTORSREQUEST_H
#define PEYOT_CHECKINSTRUCTORSREQUEST_H


#include "Request.h"

class CheckInstructorsRequest: public Request {
    std::string keyword;
    std::string flag;

public:
    CheckInstructorsRequest(std::string keyword, std::string flag): keyword(keyword), flag(flag) {
        this->type = RequestType::CHECKINSTRUCTORS;
    }

    const std::string &getKeyword1() const {
        return keyword;
    }

    void setKeyword1(const std::string &keyword) {
        CheckInstructorsRequest::keyword = keyword;
    }

    const std::string &getFlag1() const {
        return flag;
    }

    void setFlag1(const std::string &flag) {
        CheckInstructorsRequest::flag = flag;
    }

};


#endif //PEYOT_CHECKINSTRUCTORSREQUEST_H
