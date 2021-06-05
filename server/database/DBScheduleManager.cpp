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
//        size_t x = line.find("\t");
//        start_date = line.substr(0, x);
//        end_date = line.substr(x+1, line.size()-x-1);

        size_t x = line.find("\t");
        size_t y = line.find("\t", x + 1);
        size_t z = line.find("\t", y + 1);

        start_date = line.substr(0, x);
        end_date = line.substr(x+1, y-x-1);
        instructor_login = line.substr(y+1, z-y-1);
        client_login = line.substr(z+1, line.size()-z-1);



//        std::cout << "line: \t" << line << std::endl;
//        std::cout << "start: \t" << start_date << std::endl;
//        std::cout << "end: \t" << end_date << std::endl;


//        start_date = "14.05.2021 16:15";
//        end_date = "14.05.2021 16:15";
//        instructor_login = "instruktor";
//        client_login = "klient";
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
