//02.06.2021

#include "Date.h"

Date::Date() {
}

Date::Date(std::string start_date, std::string end_date) {
    set_start(start_date);
    set_end(end_date);
}

Date::Date(std::string start_date, std::string end_date, std::string instructor_login, std::string client_login) {
    set_start(start_date);
    set_end(end_date);
    this->instructor_login = std::move(instructor_login);
    this->client_login = std::move(client_login);
}

void Date::set_start(std::string date) {
    this->start_t = string_to_tm(date);
}

void Date::set_end(std::string date) {
    this->end_t = string_to_tm(date);
}

struct std::tm Date::string_to_tm(std::string date) {
//    time_t now = std::time(nullptr);
//    struct std::tm t_now = *std::localtime(&now);

    struct std::tm tm;
    std::istringstream ss(date); //date
    ss >> std::get_time(&tm, "%d.%m.%Y %H:%M");
    if (ss.fail()) {
        std::cerr << "Date::set_end error - wrong date format\n";
        throw; //?
    }

//    tm.tm_zone = t_now.tm_zone;
//    tm.tm_gmtoff = t_now.tm_gmtoff;
//    tm.tm_isdst = t_now.tm_isdst;

//
//    std::cout << "Test:" << std::endl;
//    std::cout << '\t' << tm.tm_mday << std::endl;
//    std::cout << '\t' << tm.tm_mon << std::endl;
//    std::cout << '\t' << tm.tm_year << std::endl;
//    std::cout << '\t' << tm.tm_hour << std::endl;
//    std::cout << '\t' << tm.tm_min << std::endl;

    return tm;
}

void Date::set_client_login(std::string client_login) {
    this->client_login = client_login;
}

void Date::set_instructor_login(std::string instructor_login) {
    this->instructor_login = instructor_login;
}

void Date::print() {
    std::cout << "Date {" << std::endl;
    std::cout << "\tClient: " << client_login << std::endl;
    std::cout << "\tInstructor: " << instructor_login << std::endl;
    struct std::tm tm;


    std::cout << "\tStart: " << std::put_time(&start_t, "%d.%m.%Y %H:%M")  << std::endl;

    std::cout << "\tEnd: " << std::put_time(&end_t, "%d.%m.%Y %H:%M")  << std::endl;

//    tm = *std::localtime(&start_time);
//    std::cout << "\tStart: " << std::put_time(&tm, "%d.%m.%Y %H:%M")  << std::endl;
//    std::cout << std::put_time(&tm, "%c")  << std::endl;

//    tm = *std::localtime(&end_time);
//    std::cout << "\tEnd: " << std::put_time(&tm, "%d.%m.%Y %H:%M")  << std::endl;
//    std::cout << std::put_time(&tm, "%c")  << std::endl;

    std::cout << "}" << std::endl;
}

std::string Date::to_string() {
    std::stringstream temp;
    struct std::tm tm;
//    tm = *std::localtime(&start_time);
//    temp << std::put_time(&tm, "%d.%m.%Y %H:%M");
    temp << '\t';
//    tm = *std::localtime(&end_time);
//    temp << std::put_time(&tm, "%d.%m.%Y %H:%M");
    return temp.str();
}
