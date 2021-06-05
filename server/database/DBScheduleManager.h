//02.06.2021

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
    std::vector<Date> dates;

    // lock mutex before file open
    // unlock mutex after file close
    static inline pthread_mutex_t mutex  = PTHREAD_MUTEX_INITIALIZER;

    void open();
    void close();
public:
    DBScheduleManager(std::string db_name);
    void add_date(Date date);
    bool find_date(std::string login);
    std::unique_ptr<Date> find_by_client(std::string login);
    std::unique_ptr<Date> find_by_instructor(std::string login);
    std::unique_ptr<Date> find_by_instructor_and_start(std::string login, std::string start_time);
    void find_all();
    void test_print();
};

#endif //PEYOT_DBSCHEDULEMANAGER_H
