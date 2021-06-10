//Peyot
//Szymon Kisiel
//2.06.2021

#ifndef PEYOT_DBSCHEDULEMANAGER_H
#define PEYOT_DBSCHEDULEMANAGER_H

#include <string>
#include <fstream>
#include <vector>
#include "../../structures/Date.h"

//new DBManager object when another database is accessed
class DBScheduleManager {
    std::string db_name;
    std::fstream db;

    // lock mutex before file open
    // unlock mutex after file close
    static inline pthread_mutex_t mutex  = PTHREAD_MUTEX_INITIALIZER;
    const int timeout_time_sec = 5;

    bool open();
    void close();
    void replace_and_close(const char* temp_file);
public:
    DBScheduleManager(std::string db_name);
    bool add_date(Date date);
    bool modify_date(std::string old_instructor_login, std::string old_client_login, std::string old_start_time, Date new_date);
    bool delete_date(std::string instructor_login, std::string client_login, std::string start_time);
    std::vector<Date> find_by_client(std::string login);
    std::vector<Date> find_by_instructor(std::string login);
    std::vector<Date> find_by_instructor_and_client(std::string instructor_login, std::string client_login);
    std::unique_ptr<Date> find(std::string instructor_login, std::string client_login, std::string start_time);
    std::unique_ptr<Date> find_by_instructor_and_date(std::string instructor_login, std::string start_time);
    std::vector<Date> find_all();
};

#endif //PEYOT_DBSCHEDULEMANAGER_H
