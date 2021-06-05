//4.06.2021

#include "Request.h"

Request::Request() {
    type = RequestType::REGISTER;
}

std::string Request::rtype_to_string() {
    switch(type) {
        case RequestType::QUIT:
            return "QUIT";
        case RequestType::LOGIN:
            return "LOGIN";
        case RequestType::REGISTER:
            return "REGISTER";
        case RequestType::UNREGISTER:
            return "UNREGISTER";
        case RequestType::BOOK:
            return "BOOK";
        case RequestType::RESIGN:
            return "RESIGN";
        case RequestType::MODIFY:
            return "MODIFY";
        case RequestType::CHECKMYTERMINS:
            return "CHECKMYTERMINS";
        case RequestType::CHECKINSTRUCTORS:
            return "CHECKINSTRUCTORS";
        case RequestType::CHECKTERMINSBYTRUCTOR:
            return "CHECKTERMINSBYINSTRUCTOR";
        case RequestType::SETSCHEDULE:
            return "SETSCHEDULE";
    }
}


