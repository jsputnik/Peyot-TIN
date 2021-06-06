//29.05.2021

#ifndef PEYOT_EXECUTOR_H
#define PEYOT_EXECUTOR_H


#include "../structures/User.h"
#include "security/SecurityManager.h"
#include "../parser/Request.h"
#include "../structures/Date.h"
#include "LoggedUser.h"
#include <string>
#include <memory>

class Executor {
    SecurityManager security_manager;
    std::unique_ptr<Request> request;
    std::string response;
    LoggedUser logged_user = LoggedUser::NOONE;
    std::string current_login;
public:
    Executor() = default;
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

    const std::string &getCurrentLogin() const;

    void setCurrentLogin(const std::string &currentLogin);

    const std::unique_ptr<Request> &getRequest() const;

    void setRequest(std::unique_ptr<Request> request);
};


#endif //PEYOT_EXECUTOR_H
