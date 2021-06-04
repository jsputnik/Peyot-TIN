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

