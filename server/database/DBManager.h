//26.05.2021

#ifndef PEYOT_DBMANAGER_H
#define PEYOT_DBMANAGER_H
#include <string>
#include <fstream>
#include <vector>
#include "User.h"

//tests:
//DBManager dbManager("c:/Users/kislu/CLionProjects/Database/clients");
//
//dbManager.add_user(User("test_login1", "09mlynq8rnbcpqoyncc23111", "test123"));
//dbManager.add_user(User("test_login2", "421334bn62345n9v67c4zz55", "test321"));
//
//dbManager.find_all();
//dbManager.test_print();
//
//std::cout << "mkwerc: " << dbManager.find_user("mkwerc") << std::endl;
//std::cout << "bderk: " << dbManager.find_user("bderk") << std::endl;
//std::cout << "test: " << dbManager.find_user("test") << std::endl;

//new DBManager object when another database is accessed ?
class DBManager {
    std::string db_name;
    std::fstream db;
    std::vector<User> users;

    // lock mutex before file open
    // unlock mutex after file close
    pthread_mutex_t clients_mutex  = PTHREAD_MUTEX_INITIALIZER; //should be static if multiple DBManagers are created

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
