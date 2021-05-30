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
    bool handleLogin(); //if login/register successful, automatically logs into system
    bool handleRegister();
    bool handleBook();
    bool handleResign();
    bool handleModify();
    bool handleCheck();

    const std::string &getRequest() const;
    void setRequest(const std::string &request);

};


#endif //PEYOT_UI_H
