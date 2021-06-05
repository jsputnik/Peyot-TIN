//4.06.2021

#ifndef PEYOT_CHECKTERMINSBYINSTRUCTORREQUEST_H
#define PEYOT_CHECKTERMINSBYINSTRUCTORREQUEST_H


#include "Request.h"

class CheckTerminsByInstructorRequest: public Request {
    std::string keyword;
    std::string flag;
    std::string login;

public:
    RequestType getType() const {
        return type;
    }

    CheckTerminsByInstructorRequest(const std::string &keyword, const std::string &flag, const std::string &login)
            : keyword(keyword), flag(flag), login(login) {}

    const std::string &getKeyword1() const {
        return keyword;
    }

    void setKeyword1(const std::string &keyword) {
        CheckTerminsByInstructorRequest::keyword = keyword;
    }

    const std::string &getFlag() const {
        return flag;
    }

    void setFlag(const std::string &flag) {
        CheckTerminsByInstructorRequest::flag = flag;
    }

    const std::string &getLogin() const {
        return login;
    }

    void setLogin(const std::string &login) {
        CheckTerminsByInstructorRequest::login = login;
    }
};


#endif //PEYOT_CHECKTERMINSBYINSTRUCTORREQUEST_H
