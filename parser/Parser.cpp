//Peyot
//Iwo Sokal, Illia Yatskevich
//4.06.2021

#include "Parser.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void Parser::init(string message) {
    current_index = 0;
    this->message = message;
}

std::unique_ptr<Request> Parser::parse_request() {
    unique_ptr<Request> r;
    if ((r = parse_quit_request()) != nullptr) {
        return r;
    }
    if ((r = parse_register_request()) != nullptr) {
        return r;
    }
    if ((r = parse_login_request()) != nullptr) {
        return r;
    }
    if ((r = parse_book_request()) != nullptr) {
        return r;
    }
    if ((r = parse_resign_request()) != nullptr) {
        return r;
    }
    if ((r = parse_modify_request()) != nullptr) {
        return r;
    }
    if ((r = parse_check_my_termins_request()) != nullptr) {
        return r;
    }
    if ((r = parse_check_termins_by_instructor_request()) != nullptr) {
        return r;
    }
    if ((r = parse_check_instructors_request()) != nullptr) {
        return r;
    }
    if ((r = parse_setschedule_request()) != nullptr) {
        return r;
    }
    return nullptr;
}

unique_ptr<QuitRequest> Parser::parse_quit_request() {
    current_index = 0;
    optional<string> k;
    if (current_index >= message.size() || (k = parse_keyword("quit")) == nullopt) {
        return nullptr;
    }
    return make_unique<QuitRequest>(*k);
}

unique_ptr<RegisterRequest> Parser::parse_register_request() {
    current_index = 0;
    optional<string> k;
    if (current_index >= message.size() || (k = parse_keyword("register")) == nullopt) {
        return nullptr;
    }
    if (current_index >= message.size() || message[current_index] != ' ') {
        return nullptr;
    }
    ++current_index;
    optional<string> f;
    int saved_index = current_index;
    if (current_index >= message.size()) {
        return nullptr;
    }
    if ((f = parse_flag("c")) == nullopt) {
        current_index = saved_index;
        if ((f = parse_flag("i")) == nullopt) {
            return nullptr;
        }
    }
    if (current_index >= message.size() || message[current_index] != ' ') {
        return nullptr;
    }
    ++current_index;
    optional<string> l;
    if (current_index >= message.size() || (l = parse_login()) == nullopt) {
        return nullptr;
    }
    if (current_index >= message.size() || message[current_index] != ' ') {
        return nullptr;
    }
    ++current_index;
    optional<string> p;
    if (current_index >= message.size() || (p = parse_password()) == nullopt) {
        return nullptr;
    }
    return make_unique<RegisterRequest>(*k, *f, *l, *p);
}


unique_ptr<LoginRequest> Parser::parse_login_request() {
    current_index = 0;
    optional<string> k;
    if (current_index >= message.size() || (k = parse_keyword("login")) == nullopt) {
        return nullptr;
    }
    if (current_index >= message.size() || message[current_index] != ' ') {
        return nullptr;
    }
    ++current_index;
    optional<string> l;
    if (current_index >= message.size() || (l = parse_login()) == nullopt) {
        return nullptr;
    }
    if (current_index >= message.size() || message[current_index] != ' ') {
        return nullptr;
    }
    ++current_index;
    optional<string> p;
    if (current_index >= message.size() || (p = parse_password()) == nullopt) {
        return nullptr;
    }
    return make_unique<LoginRequest>(*k, *l, *p);
}

optional<string> Parser::parse_keyword(string keyword) {
    string k;
    while(current_index < message.size()) {
        k += message[current_index];
        if (k == keyword) {
            ++current_index;
            return k;
        }
        ++current_index;
    }
    return nullopt;
}

std::optional<std::string> Parser::parse_flag(std::string flag) {
    string f;
    if (current_index >= message.size() || message[current_index] != '-') {
        return nullopt;
    }
    ++current_index;
    while(current_index < message.size()) {
        f += message[current_index];
        if (f == flag) {
            ++current_index;
            return f;
        }
        ++current_index;
    }
    return nullopt;
}

std::optional<std::string> Parser::parse_login() {
    string l;
    while(current_index < message.size() && (isalpha(message[current_index]) || isdigit(message[current_index]))) {
        l += message[current_index];
        ++current_index;
    }
    return l;
}

std::optional<std::string> Parser::parse_password() {
    string p;
    while(current_index < message.size() && !isspace(message[current_index])) {
        p += message[current_index];
        ++current_index;
    }
    return p;
}

unique_ptr<BookRequest> Parser::parse_book_request() {
    current_index = 0;
    optional<string> k;
    if (current_index >= message.size() || (k = parse_keyword("book")) == nullopt) {
        return nullptr;
    }
    if (current_index >= message.size() || message[current_index] != ' ') {
        return nullptr;
    }
    ++current_index;
    optional<string> l;
    if (current_index >= message.size() || (l = parse_login()) == nullopt) {
        return nullptr;
    }
    if (current_index >= message.size() || message[current_index] != ' ') {
        return nullptr;
    }
    ++current_index;
    optional<string> d;
    if (current_index >= message.size() || (d = parse_date()) == nullopt) {
        return nullptr;
    }
    return make_unique<BookRequest>(*k, *l, *d);
}

std::unique_ptr<ResignRequest> Parser::parse_resign_request() {
    current_index = 0;
    optional<string> k;
    if (current_index >= message.size() || (k = parse_keyword("resign")) == nullopt) {
        return nullptr;
    }
    if (current_index >= message.size() || message[current_index] != ' ') {
        return nullptr;
    }
    ++current_index;
    optional<string> l;
    if (current_index >= message.size() || (l = parse_login()) == nullopt) {
        return nullptr;
    }
    if (current_index >= message.size() || message[current_index] != ' ') {
        return nullptr;
    }
    ++current_index;
    optional<string> d;
    if (current_index >= message.size() || (d = parse_date()) == nullopt) {
        return nullptr;
    }

    return make_unique<ResignRequest>(*k, *l, *d);
}

unique_ptr<ModifyRequest> Parser::parse_modify_request() {
    current_index = 0;
    optional<string> k;
    if (current_index >= message.size() || (k = parse_keyword("modify")) == nullopt) {
        return nullptr;
    }
    if (current_index >= message.size() || message[current_index] != ' ') {
        return nullptr;
    }
    ++current_index;
    optional<string> l;
    if (current_index >= message.size() || (l = parse_login()) == nullopt) {
        return nullptr;
    }
    if (current_index >= message.size() || message[current_index] != ' ') {
        return nullptr;
    }
    ++current_index;
    optional<string> d1;
    if (current_index >= message.size() || (d1 = parse_date()) == nullopt) {
        return nullptr;
    }
    if (current_index >= message.size() || message[current_index] != ' ') {
        return nullptr;
    }
    ++current_index;
    optional<string> d2;
    if (current_index >= message.size() || (d2 = parse_date()) == nullopt) {
        return nullptr;
    }
    return make_unique<ModifyRequest>(*k, *l, *d1, *d2);
}

std::unique_ptr<CheckMyTerminsRequest> Parser::parse_check_my_termins_request() {
    current_index = 0;
    optional<string> k;
    if (current_index >= message.size() || (k = parse_keyword("check")) == nullopt) {
        return nullptr;
    }
    if (current_index >= message.size() || message[current_index] != ' ') {
        return nullptr;
    }
    ++current_index;

    optional<string> f;
    if (current_index >= message.size() || (f = parse_flag("mytermins")) == nullopt) {
        return nullptr;
    }
    return make_unique<CheckMyTerminsRequest>(*k, *f);
}

std::unique_ptr<CheckTerminsByInstructorRequest> Parser::parse_check_termins_by_instructor_request() {
    current_index = 0;
    optional<string> k;
    if (current_index >= message.size() || (k = parse_keyword("check")) == nullopt) {
        return nullptr;
    }
    if (current_index >= message.size() || message[current_index] != ' ') {
        return nullptr;
    }
    ++current_index;

    optional<string> f;
    if (current_index >= message.size() || (f = parse_flag("instermins")) == nullopt) {
        return nullptr;
    }
    if (current_index >= message.size() || message[current_index] != ' ') {
        return nullptr;
    }
    ++current_index;
    optional<string> l;
    if (current_index >= message.size() || (l = parse_login()) == nullopt) {
        return nullptr;
    }

    return make_unique<CheckTerminsByInstructorRequest>(*k, *f, *l);
}

unique_ptr<CheckInstructorsRequest> Parser::parse_check_instructors_request() {
    current_index = 0;
    optional<string> k;
    if (current_index >= message.size() || (k = parse_keyword("check")) == nullopt) {
        return nullptr;
    }
    if (current_index >= message.size() || message[current_index] != ' ') {
        return nullptr;
    }
    ++current_index;
    optional<string> f;
    if (current_index >= message.size() || (f = parse_flag("instructors")) == nullopt) {
        return nullptr;
    }
    return make_unique<CheckInstructorsRequest>(*k, *f);
}


unique_ptr<SetScheduleRequest> Parser::parse_setschedule_request() {
    current_index = 0;
    optional<string> k;
    if (current_index >= message.size() || (k = parse_keyword("setschedule")) == nullopt) {
        return nullptr;
    }
    if (current_index >= message.size() || message[current_index] != ' ') {
        return nullptr;
    }
    ++current_index;

    optional<string> d;
    if (current_index >= message.size() || (d = parse_date()) == nullopt) {
        return nullptr;
    }

    return make_unique<SetScheduleRequest>(*k, *d);
}


std::unique_ptr<Response> Parser::parse_response() {
    int first;
    std::vector<int> first_digit{1,2,3,4,5};
    if(current_index >= message.size() || !isdigit(message[current_index]) || std::find(std::begin(first_digit), std::end(first_digit), message[current_index] - '0') == std::end(first_digit)) {
        return nullptr;
    }
    first = message[current_index] - '0';
    ++current_index;
    int second;
    std::vector<int> second_digit{0,1,2,3,4,5};
    if(current_index >= message.size() || !isdigit(message[current_index]) || std::find(std::begin(second_digit), std::end(second_digit), message[current_index] - '0') == std::end(second_digit)) {
        return nullptr;
    }
    second = message[current_index] - '0';
    ++current_index;
    int third;
    std::vector<int> third_digit{0,1,2,3,4,5,6,7,8,9};
    if(current_index >= message.size() || !isdigit(message[current_index]) || std::find(std::begin(third_digit), std::end(third_digit), message[current_index] - '0') == std::end(third_digit)) {
        return nullptr;
    }
    third = message[current_index] - '0';
    ++current_index;

    if (current_index >= message.size() || message[current_index] != ' ') {
        return nullptr;
    }
    ++current_index;

    string m;
    while(current_index < message.size()) {
        m += message[current_index];
        ++current_index;
    }
    return make_unique<Response>(first, second, third, m);
}

std::optional<std::string> Parser::parse_date() {
    string date;
    if(current_index >= message.size() || !isdigit(message[current_index])) {
        return nullopt;
    }

    date += message[current_index];
    ++current_index;

    if(current_index >= message.size() || !isdigit(message[current_index])) {
        return nullopt;
    }

    date += message[current_index];
    ++current_index;

    if (current_index >= message.size() || message[current_index] != '.') {
        return nullopt;
    }

    date += message[current_index];
    ++current_index;

    if(current_index >= message.size() || !isdigit(message[current_index])) {
        return nullopt;
    }

    date += message[current_index];
    ++current_index;

    if(current_index >= message.size() || !isdigit(message[current_index])) {
        return nullopt;
    }

    date += message[current_index];
    ++current_index;

    if (current_index >= message.size() || message[current_index] != '.') {
        return nullopt;
    }

    date += message[current_index];
    ++current_index;

    if(current_index >= message.size() || !isdigit(message[current_index])) {
        return nullopt;
    }

    date += message[current_index];
    ++current_index;

    if(current_index >= message.size() || !isdigit(message[current_index])) {
        return nullopt;
    }

    date += message[current_index];
    ++current_index;

    if(current_index >= message.size() || !isdigit(message[current_index])) {
        return nullopt;
    }

    date += message[current_index];
    ++current_index;

    if(current_index >= message.size() || !isdigit(message[current_index])) {
        return nullopt;
    }

    date += message[current_index];
    ++current_index;

    if (current_index >= message.size() || message[current_index] != ' ') {
        return nullopt;
    }

    date += message[current_index];
    ++current_index;

    if(current_index >= message.size() || !isdigit(message[current_index])) {
        return nullopt;
    }

    date += message[current_index];
    ++current_index;

    if(current_index >= message.size() || !isdigit(message[current_index])) {
        return nullopt;
    }

    date += message[current_index];
    ++current_index;

    if (current_index >= message.size() || message[current_index] != ':') {
        return nullopt;
    }

    date += message[current_index];
    ++current_index;

    if(current_index >= message.size() || !isdigit(message[current_index])) {
        return nullopt;
    }

    date += message[current_index];
    ++current_index;

    if(current_index >= message.size() || !isdigit(message[current_index])) {
        return nullopt;
    }

    date += message[current_index];
    ++current_index;

    return date;
}

const string &Parser::getMessage() const {
    return message;
}

void Parser::setMessage(const string &message) {
    Parser::message = message;
}

int Parser::getCurrentIndex() const {
    return current_index;
}

void Parser::setCurrentIndex(int currentIndex) {
    current_index = currentIndex;
}







