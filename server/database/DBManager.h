//26.05.2021

#ifndef PEYOT_DBMANAGER_H
#define PEYOT_DBMANAGER_H
#include <string>
#include <fstream>
#include <vector>
#include "User.h"

//new DBManager object when another database is accessed ?
class DBManager {
    std::string db_name;
    std::fstream db;
    std::vector<User> users;

    // lock mutex before file open
    // unlock mutex after file close
    //static pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;
    void open();
    void close();
public:
    DBManager(std::string db_name);
    void add_user(User user);
    //void remove_user(std::string login);
    //void modify_user(User user); ?
    bool find_user(std::string login);
    void find_all();


    void test_print();
};


#endif //PEYOT_DBMANAGER_H
