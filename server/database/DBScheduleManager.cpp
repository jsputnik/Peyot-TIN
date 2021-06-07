//Peyot
//Szymon Kisiel
//2.06.2021

#include "DBScheduleManager.h"

void DBScheduleManager::open() {
    pthread_mutex_lock(&mutex); //should use pthread_mutex_timedlock

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
    if (line != "<start_time-end_time-instructor_login-client_login>") {
        std::cerr << db_name <<" is not schedule database" << std::endl;
        //exit()
    }
}

void DBScheduleManager::close() {
    db.close();
    pthread_mutex_unlock(&mutex);
}

void DBScheduleManager::replace_and_close(const char* temp_file) {
    db.close();
    remove(db_name.c_str());
    rename(temp_file, db_name.c_str());
    pthread_mutex_unlock(&mutex);
}

DBScheduleManager::DBScheduleManager(std::string db_name) : db_name(std::move(db_name)) {
}

void DBScheduleManager::add_date(Date date) {
    open();
    db << '\n' << date.to_string();
    close();
}

bool DBScheduleManager::modify_date(std::string old_instructor_login, std::string old_client_login,
                                    std::string old_start_time, Date new_date) {
    if (delete_date(old_instructor_login, old_client_login, old_start_time)) {
        add_date(new_date);
        return true;
    }
    return false;
}

bool DBScheduleManager::delete_date(std::string ins_login, std::string cli_login, std::string start_time) {
    open();
    bool result = false;
    std::ofstream temp;
    temp.open("../server/database/temp", std::ofstream::out);
    temp << "<SCHEDULE DATABASE>\n"
         << "<start_time-end_time-instructor_login-client_login>";
    std::string line;
    std::string start_date;
    std::string instructor_login;
    std::string client_login;
    while (!db.eof()) {
        std::getline(db, line);

        size_t t1 = line.find("\t");
        size_t t2 = line.find("\t", t1 + 1);
        size_t t3 = line.find("\t", t2 + 1);

        instructor_login = line.substr(t2 + 1, t3 - t2 - 1);
        client_login = line.substr(t3 + 1, line.size() - t3 - 1);
        start_date = line.substr(0, t1);
        if (instructor_login != ins_login || client_login != cli_login || start_date != start_time) {
            temp << '\n' << line ;
        }
        else {
            result = true;
        }
    }
    temp.close();
    replace_and_close("../server/database/temp");
    return result;
}

std::vector<Date> DBScheduleManager::find_all() {
    open();
    std::vector<Date> dates;
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
    return dates;
}

std::vector<Date> DBScheduleManager::find_by_client(std::string login) {
    open();
    std::vector<Date> result;
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
            result.push_back(Date(start_date, end_date, instructor_login, client_login));
        };
    }
    close();
    return result;
}

std::vector<Date> DBScheduleManager::find_by_instructor(std::string login) {
    open();
    std::vector<Date> result;
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
            result.push_back(Date(start_date, end_date, instructor_login, client_login));
        };
    }
    close();
    return result;
}

std::vector<Date>DBScheduleManager::find_by_instructor_and_client(std::string ins_login, std::string cli_login) {
    open();
    std::vector<Date> result;
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
        client_login = line.substr(t3 + 1, line.size() - t3 - 1);
        if (instructor_login == ins_login && client_login == cli_login) {
            start_date = line.substr(0, t1);
            end_date = line.substr(t1 + 1, t2 - t1 - 1);
            result.push_back(Date(start_date, end_date, instructor_login, client_login));
        };
    }
    close();
    return result;
}

std::unique_ptr<Date> DBScheduleManager::find(std::string ins_login, std::string cli_login, std::string start_time) {
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
        client_login = line.substr(t3 + 1, line.size() - t3 - 1);
        start_date = line.substr(0, t1);
        if (instructor_login == ins_login && client_login == cli_login && start_date == start_time) {
            end_date = line.substr(t1 + 1, t2 - t1 - 1);
            close();
            return std::make_unique<Date>(start_date, end_date, instructor_login, client_login);
        };
    }
    close();
    return nullptr;
}

std::unique_ptr<Date>DBScheduleManager::find_by_instructor_and_date(std::string ins_login, std::string start_time) {
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
        instructor_login = line.substr(t2 + 1, t3 - t2 - 1);
        if (instructor_login == ins_login && start_date == start_time) {
            client_login = line.substr(t3 + 1, line.size() - t3 - 1);
            end_date = line.substr(t1 + 1, t2 - t1 - 1);
            close();
            return std::make_unique<Date>(start_date, end_date, instructor_login, client_login);
        };
    }
    close();
    return nullptr;
}
