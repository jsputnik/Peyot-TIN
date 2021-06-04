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
    }
}


