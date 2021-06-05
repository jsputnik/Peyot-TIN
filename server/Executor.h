//29.05.2021

#ifndef PEYOT_EXECUTOR_H
#define PEYOT_EXECUTOR_H


#include "../structures/User.h"
#include "security/SecurityManager.h"
#include "../parser/Request.h"
#include "../structures/Date.h"
#include <string>
#include <memory>

class Executor {
    SecurityManager security_manager;
    std::unique_ptr<Request> request;
    std::string response;
public:
    Executor(std::unique_ptr<Request> request);
    void execute();
    void quitConnection();
    void loginUser();
    void registerUser();
    void unregisterUser();
    void resign();

    void setResponse(const std::string &response);

    const std::string &getResponse() const;
};


#endif //PEYOT_EXECUTOR_H
