//
// Created by szymon on 6/2/21.
//

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
};


#endif //PEYOT_DATE_H
