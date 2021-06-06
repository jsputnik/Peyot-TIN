//26.05.2021

#include "DBManager.h"
#include "../security/SecurityManager.h"
#include <iostream>

using namespace std;

DBManager::DBManager(string db_name) : db_name(db_name) {
}

void DBManager::open() {
    pthread_mutex_lock(&mutex); //should use pthread_mutex_timedlock

    db.open(db_name, std::ios::in | std::ios::out | std::ios_base::app); //TODO (?): mode parameter: ios::in for input only, ios::out for output only
    if (!db.good()) {
        cerr << "Can't open file: " << db_name << endl;
        //exit() ?
    }
    std::string line;
    std::getline(db, line);
    if (line != "<CLIENTS DATABASE>" && line != "<EMPLOYEES DATABASE>") {
        cerr << db_name << " is not clients/employees database" << endl;
        //exit()
    }

    std::getline(db, line);
    if (line != "<login-hashed_passwd-salt>") {
        cerr << db_name <<" is not clients/employees database" << endl;
        //exit()
    }
}

void DBManager::close() {
    db.close();
    pthread_mutex_unlock(&mutex);
}

std::unique_ptr<User> DBManager::find_user(std::string user_login) {
    open();
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
    open();
    std::vector<User> users;
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

void DBManager::add_user(User newUser) {
    open();
    db << '\n' << newUser.getLogin();
    db << '\t' << newUser.getHashedPassword();
    db << '\t' << newUser.getSalt();
    close();
}

void DBManager::setDbName(const string &dbName) {
    db_name = dbName;
}
