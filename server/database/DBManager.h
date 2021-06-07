//Peyot
//Szymon Kisiel
//26.05.2021

#ifndef PEYOT_DBMANAGER_H
#define PEYOT_DBMANAGER_H
#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include "../../structures/User.h"

//new DBManager object when another database is accessed ?
class DBManager {
    std::string db_name;
    std::fstream db;

    // lock mutex before file open
    // unlock mutex after file close
    static inline pthread_mutex_t mutex  = PTHREAD_MUTEX_INITIALIZER;

    void open();
    void close();
public:
    DBManager(std::string db_name);
    void add_user(User user);
    //void remove_user(std::string login);
    //void modify_user(User user); ?
    std::unique_ptr<User> find_user(std::string login);
    std::vector<User> find_all();

    void setDbName(const std::string &dbName);
};


#endif //PEYOT_DBMANAGER_H
