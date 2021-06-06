//02.06.2021

#ifndef PEYOT_DATE_H
#define PEYOT_DATE_H

#include <ctime>
#include <string>
#include <iomanip>
#include <iostream>

class Date {
    struct std::tm start_t;
    struct std::tm end_t;

    std::string client_login;
    std::string instructor_login;
public:
    Date();
    Date(std::string start_date, std::string end_date);
    Date(std::string start_date, std::string end_date, std::string instructor_login, std::string client_login);
    Date(std::string start_date);
    void set_start(std::string date);
    void set_end(std::string date);
    static struct std::tm string_to_tm(std::string date);
    void set_client_login(std::string client_login);
    void set_instructor_login(std::string instructor_login);
    void print();
    std::string to_string();
};


#endif //PEYOT_DATE_H
