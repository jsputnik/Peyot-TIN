//6.06.2021

#ifndef PEYOT_SETSCHEDULEREQUEST_H
#define PEYOT_SETSCHEDULEREQUEST_H

#include "Request.h"


class SetScheduleRequest: public Request {
    std::string keyword;
    std::string date;
};


#endif //PEYOT_SETSCHEDULEREQUEST_H
