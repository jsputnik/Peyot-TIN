//02.06.2021

#ifndef PEYOT_DATE_H
#define PEYOT_DATE_H

#include <ctime>
#include <string>
#include <iomanip>
#include <iostream>

class Date {
    std::time_t start_time;
    std::time_t end_time;
public:
    Date();
    void set_start(std::string date);
    void set_end(std::string date);
    void print();
    std::string to_string();
};


#endif //PEYOT_DATE_H
