//26.05.2021

#include "DBManager.h"
#include <iostream>

using namespace std;

DBManager::DBManager(string db_name) {
    db.open(db_name, std::ios::in | std::ios::out); //TODO (?): mode parameter: ios::in for input only, ios::out for output only
    if (!db.good()) {
        cerr << "Can't open file: " << db_name << endl;
        //exit() ?
    }
}

bool DBManager::find_user(std::string login) {
    //TODO
    //if user.login==login and user.passwd==paswd return true ?
    return true;
}

void DBManager::close() {
    db.close();
}


