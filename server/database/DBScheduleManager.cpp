//02.06.2021

#include "DBScheduleManager.h"

void DBScheduleManager::open() {
    //pthread_mutex_lock(&clients_mutex); //should use pthread_mutex_timedlock

    db.open(db_name, std::ios::in | std::ios::out | std::ios_base::app); //TODO (?): mode parameter: ios::in for input only, ios::out for output only
    if (!db.good()) {
        std::cerr << "Can't open file: " << db_name << std::endl;
        //exit() ?
    }
    std::string line;
    std::getline(db, line);
    if (line != "<SCHEDULE DATABASE>") {
        std::cerr << db_name << " is not schedule database" << std::endl;
        //exit()
    }


    std::getline(db, line);
    if (line != "<start_time-end_time>") {
        std::cerr << db_name <<" is not schedule database" << std::endl;
        //exit()
    }
}

void DBScheduleManager::close() {
    db.close();
}

DBScheduleManager::DBScheduleManager(std::string db_name) : db_name(std::move(db_name)) {
}

void DBScheduleManager::add_date(Date date) {
    open();
    db << '\n' << date.to_string();
    close();
}

void DBScheduleManager::find_all() {
    open();
    std::string line;
    std::string start_date;
    std::string end_date;
    std::string instructor_login;
    std::string client_login;
    while (!db.eof()) {
        std::getline(db, line);

        size_t t1 = line.find("\t");
        size_t t2 = line.find("\t", t1 + 1);
        size_t t3 = line.find("\t", t2 + 1);

        start_date = line.substr(0, t1);
        end_date = line.substr(t1 + 1, t2 - t1 - 1);
        instructor_login = line.substr(t2 + 1, t3 - t2 - 1);
        client_login = line.substr(t3 + 1, line.size() - t3 - 1);

        dates.push_back(Date(start_date, end_date, instructor_login, client_login));
    }
    close();
}

void DBScheduleManager::test_print() {
    std::cout << "Schedule:" << std::endl;
    for (Date date : dates) {
        date.print();
        //std::cout << date.to_string() << std::endl;
    }
}

std::unique_ptr<Date> DBScheduleManager::find_by_client(std::string login) {
    open();
    std::string line;
    std::string start_date;
    std::string end_date;
    std::string instructor_login;
    std::string client_login;
    while (!db.eof()) {
        std::getline(db, line);

        size_t t1 = line.find("\t");
        size_t t2 = line.find("\t", t1 + 1);
        size_t t3 = line.find("\t", t2 + 1);

        client_login = line.substr(t3 + 1, line.size() - t3 - 1);
        if (client_login == login) {
            start_date = line.substr(0, t1);
            end_date = line.substr(t1 + 1, t2 - t1 - 1);
            instructor_login = line.substr(t2 + 1, t3 - t2 - 1);
            close();
            return std::make_unique<Date>(start_date, end_date, instructor_login, client_login);
        };
    }
    close();
    return nullptr;
}

std::unique_ptr<Date> DBScheduleManager::find_by_instructor(std::string login) {
    open();
    std::string line;
    std::string start_date;
    std::string end_date;
    std::string instructor_login;
    std::string client_login;
    while (!db.eof()) {
        std::getline(db, line);

        size_t t1 = line.find("\t");
        size_t t2 = line.find("\t", t1 + 1);
        size_t t3 = line.find("\t", t2 + 1);

        instructor_login = line.substr(t2 + 1, t3 - t2 - 1);
        if (instructor_login == login) {
            start_date = line.substr(0, t1);
            end_date = line.substr(t1 + 1, t2 - t1 - 1);
            client_login = line.substr(t3 + 1, line.size() - t3 - 1);
            close();
            return std::make_unique<Date>(start_date, end_date, instructor_login, client_login);
        };
    }
    close();
    return nullptr;
}

std::unique_ptr<Date> DBScheduleManager::find_by_instructor_and_start(std::string login, std::string start_time) {
    return nullptr;
}
