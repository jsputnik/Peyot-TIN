//29.05.2021

#ifndef PEYOT_UI_H
#define PEYOT_UI_H
#include <string>
#include "../Client.h"


class UI {
    Client client;
    std::string request;
public:
    UI(Client client);
    void get_request();
    bool handle_request();
    bool handle_response();
    bool help();

    const std::string &getRequest() const;
    void setRequest(const std::string &request);

};


#endif //PEYOT_UI_H
