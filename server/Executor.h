//29.05.2021

#ifndef PEYOT_EXECUTOR_H
#define PEYOT_EXECUTOR_H


#include "../structures/User.h"
#include "security/SecurityManager.h"
#include "../parser/Request.h"
#include "../structures/Date.h"
#include "eventLog/ELManager.h"
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
    void book();
    void resign();
    void modify();
    void check_my_termins();
    void check_termins_by_instructor();

    void setResponse(const std::string &response);

    const std::string &getResponse() const;
};


#endif //PEYOT_EXECUTOR_H
