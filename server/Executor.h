//29.05.2021

#ifndef PEYOT_EXECUTOR_H
#define PEYOT_EXECUTOR_H


#include "database/User.h"
#include "security/SecurityManager.h"
#include <string>

class Executor {
    SecurityManager security_manager;
    std::string request;
    std::string response;
public:
    Executor(std::string request);
    void execute();
    void quitConnection();
    void loginUser();
    void registerUser();
    void unregisterUser();

    void setResponse(const std::string &response);

    const std::string &getResponse() const;
};


#endif //PEYOT_EXECUTOR_H
