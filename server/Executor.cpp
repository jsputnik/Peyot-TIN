//Peyot
//Iwo Sokal, Szymon Kisiel, Olgierd Sobieraj, Illia Yatskevich
//29.05.2021

#include "Executor.h"
#include "database/DBManager.h"
#include "database/DBScheduleManager.h"
#include "eventLog/ELManager.h"
#include <iostream>
#include <openssl/sha.h>

using namespace std;

Executor::Executor(unique_ptr<Request> request) {
    this->request = std::move(request);
}

//return response ?
void Executor::execute() {
    if (request == nullptr) {
        setResponse("220 Couldn't parse request");
        return;
    }
    if (request->getType() == RequestType::QUIT) {
        logged_user = LoggedUser::NOONE;
        setResponse("400 Logged out");
        return;
    }
    if (request->getType() == RequestType::REGISTER) {
        registerUser();
        return;
    }
    if (request->getType() == RequestType::LOGIN) {
        loginUser();
        return;
    }
    if (request->getType() == RequestType::BOOK) {
        book();
        return;
    }
    if (request->getType() == RequestType::RESIGN) {
        resign();
        return;
    }
    if (request->getType() == RequestType::MODIFY) {
        modify();
        return;
    }
    if (request->getType() == RequestType::CHECKMYTERMINS) {
        check_my_termins();
        return;
    }
    if (request->getType() == RequestType::CHECKTERMINSBYTRUCTOR) {
        check_termins_by_instructor();
        return;
    }
    if (request->getType() == RequestType::CHECKINSTRUCTORS) {
        check_instructors();
        return;
    }
    if (request->getType() == RequestType::SETSCHEDULE) {
        set_schedule();
        return;
    }
    setResponse("350 Internal error: parsed undefined message");
}

void Executor::loginUser() {
    string login = request->getLogin();
    string password = request->getPassword();
    if (logged_user != LoggedUser::NOONE) {
        setResponse("240 Login unsuccessful: already logged in as: " + current_login);
        return;
    }
    DBManager dbManager("../server/database/clients");
    std::unique_ptr<User> user = dbManager.find_user(login);
    logged_user = LoggedUser::CLIENT;
    if (user == nullptr) {
        dbManager.setDbName("../server/database/employees");
        if ((user = dbManager.find_user(login)) == nullptr) {
            setResponse("210 Login unsuccessful: user doesn't exist");
            logged_user = LoggedUser::NOONE;
            return;
        }
        logged_user = LoggedUser::INSTRUCTOR;
    }

    string salt_string = user->getSalt();
    string hash_string = user->getHashedPassword();
    unsigned char* salt = reinterpret_cast<unsigned char*>(const_cast<char*>(salt_string.c_str()));
    unsigned char hash_result[SHA512_DIGEST_LENGTH];
    unsigned char encoded_hash_result[4*(SHA512_DIGEST_LENGTH+2)/3];
    security_manager.hash_password(SecurityManager::merge_salt_with_password(salt, security_manager.getEncodedSaltLength(), password), hash_result, encoded_hash_result, SHA512_DIGEST_LENGTH);
    string encoded_hash_result_string = reinterpret_cast<char*>(encoded_hash_result);
    if (hash_string == encoded_hash_result_string) {
        current_login = login;
        setResponse("100 Login successful");
        return;
    }
    logged_user = LoggedUser::NOONE;
    setResponse("240 Login unsuccessful: wrong password");
}

void Executor::registerUser() {
    string login = request->getLogin();
    string password = request->getPassword();
    if (logged_user != LoggedUser::NOONE) {
        setResponse("241 Registration unsuccessful: can't register while logged in as: " + current_login);
        return;
    }
    DBManager dbManager("../server/database/clients");
    std::unique_ptr<User> user = dbManager.find_user(login);
    if (user != nullptr) {
        setResponse("211 Registration unsuccessful: user already registered");
        return;
    }
    dbManager.setDbName("../server/database/employees");
    if ((user = dbManager.find_user(login)) != nullptr) {
        setResponse("211 Registration unsuccessful: instructor already registered");
        return;
    }
    if (request->getFlag() == "c") {
        dbManager.setDbName("../server/database/clients");
    }
    unsigned char salt[security_manager.getNotEncodedSaltLength()];
    unsigned char encoded_salt[security_manager.getEncodedSaltLength()];
    security_manager.generate_salt(encoded_salt, salt, security_manager.getNotEncodedSaltLength()); //encoded_salt_length
    unsigned char hash[SHA512_DIGEST_LENGTH];
    unsigned char encoded_hash[4*(SHA512_DIGEST_LENGTH+2)/3];
    security_manager.hash_password(SecurityManager::merge_salt_with_password(encoded_salt, security_manager.getEncodedSaltLength(), password), hash, encoded_hash, SHA512_DIGEST_LENGTH);

    string hash_string = reinterpret_cast<char*>(encoded_hash);
    string salt_string = reinterpret_cast<char*>(encoded_salt);
    dbManager.add_user(User(login, hash_string, salt_string));
    setResponse("101 Registration successful");
}

void Executor::setResponse(const string &response) {
    ELManager elManager("../server/eventLog/logs");
    elManager.save(response + "\n");
    elManager.close();

    Executor::response = response;
}

const string &Executor::getResponse() const {
    return response;
}

void Executor::book() {
    if (logged_user != LoggedUser::CLIENT) {
        setResponse("222 Reservation unsuccessful: must log in to book in");
        return;
    }
    string instructor_login = request->getLogin();
    string start_time = request->getDate();
    DBScheduleManager dbManager("../server/database/schedule");
    unique_ptr<Date> date = dbManager.find(instructor_login, "-", start_time);
    if (date == nullptr) {
        setResponse("222 Reservation unsuccessful: date doesn't exist or is already booked");
        return;
    }
    Date new_date(start_time, date->get_end(), instructor_login, current_login);
    if (!dbManager.modify_date(instructor_login, "-", start_time, new_date)) {
        setResponse("212 Reservation unsuccessful: couldn't book in");
        return;
    }
    setResponse("102 Reservation successful");
}

void Executor::resign() {
    if (logged_user != LoggedUser::CLIENT && logged_user != LoggedUser::INSTRUCTOR) {
        setResponse("243 Resign unsuccessful: must log in to resign");
        return;
    }
    string login = request->getLogin();
    string resign_date = request->getDate();
    DBScheduleManager dbManager("../server/database/schedule");
    unique_ptr<Date> date;
    if (logged_user == LoggedUser::CLIENT) {
        date = dbManager.find(login, current_login, resign_date);
    }
    else {
        date = dbManager.find(current_login, login, resign_date);
    }
    if (date == nullptr) {
        setResponse("213 Resign unsuccessful: date doesn't exist");
        return;
    }
    if (logged_user == LoggedUser::CLIENT) {
        if(!dbManager.delete_date(login, current_login, resign_date)){
            setResponse("313 Resign unsuccessful: couldn't resign");
            return;
        }
    }
    else {
        if(!dbManager.delete_date(current_login, login, resign_date)){
            setResponse("313 Resign unsuccessful: couldn't resign");
            return;
        }
    }
    setResponse("103 Resign successful");
}

void Executor::modify() {
    if (logged_user != LoggedUser::CLIENT) {
        setResponse("244 Modification unsuccessful: must log in to modify");
        return;
    }
    string instructor_login = request->getLogin();
    string old_start_time = request->getOldDate();
    string new_start_time = request->getNewDate();
    DBScheduleManager dbManager("../server/database/schedule");
    unique_ptr<Date> date = dbManager.find(instructor_login, current_login, old_start_time);
    if (date == nullptr) {
        setResponse("214 Modification unsuccessful: date doesn't exist");
        return;
    }
    string new_end_time = calculate_end_time(new_start_time);
    Date new_date = Date(new_start_time, new_end_time, instructor_login, current_login);
    if (!dbManager.modify_date(instructor_login, current_login, old_start_time, new_date)) {
        setResponse("314 Modification unsuccessful: Couldn't modify");
        return;
    }
    setResponse("104 Modification successful");
}

void Executor::check_my_termins() {
    DBScheduleManager dbManagerTermins("../server/database/schedule");
    string check_my_termins;
    auto termins = dbManagerTermins.find_by_client(current_login);

    if(termins.empty()){
        setResponse("225 Check unsuccessful");
        return;
    }
    check_my_termins = "105 Check successful : ";
    for(auto termin : termins){
        check_my_termins += termin.get_start() + " " + termin.get_end() + " " + termin.get_instructor() + "\n";
    }

    setResponse(check_my_termins);
}

void Executor::check_termins_by_instructor() {
    DBScheduleManager dbManagerTermins("../server/database/schedule");
    string check_termins_by_instructor_response;
    auto termins = dbManagerTermins.find_by_instructor_and_client(request->getLogin(),"-");

    if(termins.empty()){
        setResponse("226 Check unsuccessful");
        return;
    }
    check_termins_by_instructor_response = "106 Check successful : \n";
    for(auto termin : termins){
        check_termins_by_instructor_response += termin.get_start() + " " + termin.get_end() + "\n";
    }

    setResponse(check_termins_by_instructor_response);
}

void Executor::check_instructors() {
    DBManager dbManagerEmployees("../server/database/employees");
    string check_instructors_response;
    auto employees = dbManagerEmployees.find_all();
    if(employees.empty()){
        setResponse("227 Check unsuccessful");
        return;
    }
    check_instructors_response = "107 Check successful : ";
    for(auto employee : employees){
        check_instructors_response += employee.getLogin() + " ";
    }
    setResponse(check_instructors_response);
}

void Executor::set_schedule() {
    if (logged_user != LoggedUser::INSTRUCTOR) {
        setResponse("249 SetSchedule unsuccessful: permission denied");
        return;
    }
    DBScheduleManager dbManager("../server/database/schedule");
    if (dbManager.find_by_instructor_and_date(current_login, request->getDate()) != nullptr) {
        setResponse("219 SetSchedule unsuccessful: date already set");
        return;
    }
    dbManager.add_date(Date(request->getDate(), calculate_end_time(request->getDate()), current_login, "-"));
    setResponse("109 SetSchedule successful");
}


string Executor::calculate_end_time(string start_time) {
    struct tm end_time = {0};
    end_time.tm_isdst = -1;
    strptime(start_time.c_str(), "%d.%m.%Y %H:%M", &end_time);
    time_t converted_end_time = mktime(&end_time);
    converted_end_time += (60*60 * 1.5);
    end_time = *localtime(&converted_end_time);
    stringstream ss;
    ss << put_time(&end_time, "%d.%m.%Y %H:%M");
    return ss.str();
}


const string &Executor::getCurrentLogin() const {
    return current_login;
}

void Executor::setCurrentLogin(const string &currentLogin) {
    current_login = currentLogin;
}

const unique_ptr<Request> &Executor::getRequest() const {
    return request;
}

void Executor::setRequest(unique_ptr<Request> request) {
    this->request = std::move(request);
}

void Executor::start_timer() {
    timer = std::chrono::high_resolution_clock::now();
}

bool Executor::check_timeout(int seconds) {
    auto stop = std::chrono::high_resolution_clock::now();
    if(std::chrono::duration_cast<std::chrono::seconds>(stop-timer).count() >= seconds)
        return true;
    return false;
}
