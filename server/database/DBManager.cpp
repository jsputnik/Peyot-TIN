//26.05.2021

#include "DBManager.h"
#include <iostream>

using namespace std;

DBManager::DBManager(string db_name) : db_name(db_name) {
}

void DBManager::open() {
    //lock mutex
    db.open(db_name, std::ios::in | std::ios::out | std::ios_base::app); //TODO (?): mode parameter: ios::in for input only, ios::out for output only
    if (!db.good()) {
        cerr << "Can't open file: " << db_name << endl;
        //exit() ?
    }
    std::string line;
    std::getline(db, line);
    if (line != "<CLIENTS DATABASE>")
        cerr << "File is not clients database" << endl;

    std::getline(db, line);
    if (line != "<login-hashed_passwd-salt>")
        cerr << "File is not clients database" << endl;
}

void DBManager::close() {
    db.close();
    //unlock mutex
}

bool DBManager::find_user(std::string user_login) {
//    if user.login==login and user.passwd==paswd return true ?
//    for (User user : users) {
//        if (user.getLogin() == login)
//            return true;
//    }
//    return false;
    open();
    std::string login;
    std::string hashed_password;
    std::string salt;
    while (!db.eof()) {
        db >> login;
        if (login == user_login) {
            close();
            return true;
        }
        db >> hashed_password;
        db >> salt;
    }
    close();
    return false;
}


void DBManager::find_all() {
    open();
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
}

void DBManager::add_user(User newUser) {
    open();
    db << '\n' << newUser.getLogin();
    db << '\t' << newUser.getHashedPassword();
    db << '\t' << newUser.getSalt();
    close();
}

void DBManager::test_print() {
    cout << "Users:" << endl;
    for (User user : users) {
        cout << user.getLogin() << '\t' << user.getHashedPassword() << '\t' << user.getSalt() << endl;
    }
}
