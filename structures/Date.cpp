//02.06.2021

#include "Date.h"

Date::Date() : start_time(std::time(nullptr)), end_time(std::time(nullptr))  {
}

Date::Date(std::string start_date, std::string end_date) {
    set_start(start_date);
    set_end(end_date);
}

void Date::set_start(std::string date) {
    time_t now = std::time(nullptr);
    struct std::tm t_now = *std::localtime(&now);

    struct std::tm tm;
    std::istringstream ss(date);
    ss >> std::get_time(&tm, "%d.%m.%Y %H:%M");
    if (ss.fail()) {
        std::cerr << "Date::set_start error - wrong date format\n";
        return;
    }
    tm.tm_zone = t_now.tm_zone;
    tm.tm_gmtoff = t_now.tm_gmtoff;
    tm.tm_isdst = t_now.tm_isdst;
    start_time = mktime(&tm);
}

void Date::set_end(std::string date) {
    time_t now = std::time(nullptr);
    struct std::tm t_now = *std::localtime(&now);

    struct std::tm tm;
    std::istringstream ss(date);
    ss >> std::get_time(&tm, "%d.%m.%Y %H:%M");
    if (ss.fail()) {
        std::cerr << "Date::set_start error - wrong date format\n";
        return;
    }
    tm.tm_zone = t_now.tm_zone;
    tm.tm_gmtoff = t_now.tm_gmtoff;
    tm.tm_isdst = t_now.tm_isdst;
    end_time = mktime(&tm);
}

void Date::print() {
    struct std::tm tm;

    tm = *std::localtime(&start_time);
    std::cout << "Start: " << std::put_time(&tm, "%d.%m.%Y %H:%M")  << std::endl;
    //std::cout << std::put_time(&tm, "%c")  << std::endl;

    tm = *std::localtime(&end_time);
    std::cout << "End: " << std::put_time(&tm, "%d.%m.%Y %H:%M")  << std::endl;
    //std::cout << std::put_time(&tm, "%c")  << std::endl;
}

std::string Date::to_string() {
    std::stringstream temp;
    struct std::tm tm;
    tm = *std::localtime(&start_time);
    temp << std::put_time(&tm, "%d.%m.%Y %H:%M");
    temp << '\t';
    tm = *std::localtime(&end_time);
    temp << std::put_time(&tm, "%d.%m.%Y %H:%M");
    return temp.str();
}
