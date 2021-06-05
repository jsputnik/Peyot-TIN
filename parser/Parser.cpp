//4.06.2021

#include "Parser.h"
#include <iostream>

using namespace std;

std::unique_ptr<Request> Parser::parse_request() {
    unique_ptr<Request> r;
    if ((r = parse_quit_request()) != nullptr) {
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
    if ((r = parse_check_my_termins_request()) != nullptr) {
        return r;
    }
    if ((r =  parse_check_termins_by_instructor_request()) != nullptr) {
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
    return make_unique<LoginRequest>(*k, User(*l, *p, ""));
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
    return make_unique<BookRequest>(*k, *l, Date(*d));
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

    return make_unique<ResignRequest>(*k, *l, Date(*d));
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







