//Peyot
//Iwo Sokal
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

    const std::string &getKeyword() const {
        return keyword;
    }

    void setKeyword(const std::string &keyword) {
        CheckInstructorsRequest::keyword = keyword;
    }

    const std::string &getFlag() const {
        return flag;
    }

    void setFlag(const std::string &flag) {
        CheckInstructorsRequest::flag = flag;
    }

};


#endif //PEYOT_CHECKINSTRUCTORSREQUEST_H
