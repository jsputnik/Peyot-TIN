//26.05.2021

#ifndef PEYOT_DBMANAGER_H
#define PEYOT_DBMANAGER_H
#include <string>
#include <fstream>

//new DBManager object when another database is accessed ?
class DBManager {
    std::fstream db;
public:
    DBManager(std::string db_name);
    void open(); //open file
    //void add_user(User user);
    //void remove_user(std::string login);
    //void modify_user(User user); ?
    bool find_user(std::string login);
    void close();
};


#endif //PEYOT_DBMANAGER_H
