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
    Date() : start_time(std::time(nullptr)), end_time(std::time(nullptr))  {
    }
    void print() {
        struct std::tm tm;

        tm = *std::localtime(&start_time);
        std::cout << std::put_time(&tm, "%d.%m.%Y %H:%M")  << std::endl;
        //std::cout << std::put_time(&tm, "%c")  << std::endl;

        tm = *std::localtime(&end_time);
        std::cout << std::put_time(&tm, "%d.%m.%Y %H:%M")  << std::endl;
        //std::cout << std::put_time(&tm, "%c")  << std::endl;
    }
    void set_time(/*int h, int m, int s*/) {
        struct std::tm tm;
        std::istringstream ss("16.05.2021 16:31");
        ss >> std::get_time(&tm, "%d.%m.%Y %H:%M");
        start_time = mktime(&tm);
    }
};


#endif //PEYOT_DATE_H
