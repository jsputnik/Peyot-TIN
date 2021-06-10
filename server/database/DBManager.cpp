//Peyot
//Szymon Kisiel
//26.05.2021

#include "DBManager.h"
#include "../security/SecurityManager.h"
#include <iostream>

using namespace std;

DBManager::DBManager(string db_name) : db_name(db_name) {
}

bool DBManager::open() {
    struct timespec timeout_time;
    clock_gettime(CLOCK_REALTIME, &timeout_time);
    timeout_time.tv_sec += timeout_time_sec;
    int error_num = pthread_mutex_timedlock(&mutex, &timeout_time);
    if (error_num == ETIMEDOUT) {
        std::cout << "TIMED OUT" << std::endl;
        return false; //throw
    }
    else if (error_num != 0)
        return false; //throw

    db.open(db_name, std::ios::in | std::ios::out | std::ios_base::app); //TODO (?): mode parameter: ios::in for input only, ios::out for output only
    if (!db.good()) {
        cerr << "Can't open file: " << db_name << endl;
        return false; //throw
    }
    std::string line;
    std::getline(db, line);
    if (line != "<CLIENTS DATABASE>" && line != "<EMPLOYEES DATABASE>") {
        cerr << db_name << " is not clients/employees database" << endl;
        return false; //throw
    }

    std::getline(db, line);
    if (line != "<login-hashed_passwd-salt>") {
        cerr << db_name <<" is not clients/employees database" << endl;
        return false; //throw
    }
    return true;
}

void DBManager::close() {
    db.close();
    pthread_mutex_unlock(&mutex);
}

std::unique_ptr<User> DBManager::find_user(std::string user_login) {
    if (!open())
        return nullptr;
    std::string login;
    std::string hashed_password;
    std::string salt;

    bool found_user = false;
    while (!db.eof() && !found_user) {
        db >> login;
        if (login == user_login) {
            found_user = true;
        }
        db >> hashed_password;
        db >> salt;
    }
    close();
    if (found_user)
        return std::make_unique<User>(login, hashed_password, salt);
    return nullptr;
}


std::vector<User> DBManager::find_all() {
    std::vector<User> users;
    if (!open())
        return users;
    std::string login;
    std::string hashed_password;
    std::string salt;
    while (!db.eof()) {
        db >> login;
        db >> hashed_password;
        db >> salt;
        users.push_back(User(login, hashed_password, salt));
    }
    close();
    return users;
}

bool DBManager::add_user(User newUser) {
    if (!open())
        return false;
    db << '\n' << newUser.getLogin();
    db << '\t' << newUser.getHashedPassword();
    db << '\t' << newUser.getSalt();
    close();
    return true;
}

void DBManager::setDbName(const string &dbName) {
    db_name = dbName;
}
