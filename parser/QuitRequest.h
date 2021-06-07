//Peyot
//Iwo Sokal
//4.06.2021

#ifndef PEYOT_QUITREQUEST_H
#define PEYOT_QUITREQUEST_H

#include "Request.h"

class QuitRequest: public Request {
    std::string keyword;

public:
    QuitRequest(std::string keyword): keyword(keyword) {
        type = RequestType::QUIT;
    }

    RequestType getType() const {
        return type;
    }

    const std::string &getKeyword() const {
        return keyword;
    }

    void setKeyword(const std::string &keyword) {
        this->keyword = keyword;
    }
};


#endif //PEYOT_QUITREQUEST_H
