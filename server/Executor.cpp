//29.05.2021

#include "Executor.h"
#include "database/DBManager.h"
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

    //if request == login -> loginUser
    //if request == register -> registerUser
    //...
    setResponse("UNASSIGNED RESPONSE");
}

void Executor::loginUser() {
    string login = request->getLogin();
    string password = request->getPassword();
    DBManager dbManager("../server/database/clients");
    std::unique_ptr<User> user = dbManager.find_user(login);
    if (user == nullptr) {
        setResponse("240 Login unsuccessful");
        return; //user not found
    }
    string salt_string = user->getSalt();
    string hash_string = user->getHashedPassword();
    unsigned char* salt = reinterpret_cast<unsigned char*>(const_cast<char*>(salt_string.c_str()));
    unsigned char hash_result[SHA512_DIGEST_LENGTH];
    unsigned char encoded_hash_result[4*(SHA512_DIGEST_LENGTH+2)/3];
    security_manager.hash_password(SecurityManager::merge_salt_with_password(salt, security_manager.getEncodedSaltLength(), password), hash_result, encoded_hash_result, SHA512_DIGEST_LENGTH);
    string encoded_hash_result_string = reinterpret_cast<char*>(encoded_hash_result);
    if (hash_string == encoded_hash_result_string) {
        setResponse("100 Login successful");
        return;
    }
    setResponse("240 Login unsuccessful");
    //wrong password
}

void Executor::registerUser() {
    cout << "In register()" << endl;
    string login = request->getLogin();
    string password = request->getPassword();
    DBManager dbManager("../server/database/clients");
    std::unique_ptr<User> user = dbManager.find_user(login);
    if (user != nullptr) {
        setResponse("241 Register unsuccessful");
        return; //user already exists
    }
    unsigned char salt[security_manager.getNotEncodedSaltLength()];
    unsigned char encoded_salt[security_manager.getEncodedSaltLength()];
    security_manager.generate_salt(encoded_salt, salt, security_manager.getNotEncodedSaltLength()); //encoded_salt_length
    unsigned char hash[SHA512_DIGEST_LENGTH];
    unsigned char encoded_hash[4*(SHA512_DIGEST_LENGTH+2)/3];
    security_manager.hash_password(SecurityManager::merge_salt_with_password(encoded_salt, security_manager.getEncodedSaltLength(), password), hash, encoded_hash, SHA512_DIGEST_LENGTH);

    //cast unsigned char to char
    string hash_string = reinterpret_cast<char*>(encoded_hash);
    string salt_string = reinterpret_cast<char*>(encoded_salt);
    dbManager.add_user(User(login, hash_string, salt_string));
    setResponse("101 Registration successful");
}

void Executor::setResponse(const string &response) {
    Executor::response = response;
}

const string &Executor::getResponse() const {
    return response;
}

void Executor::book() {
    cout << "In book()" << endl;
    setResponse("240 Login unsuccessful");
}

void Executor::resign() {
    cout << "In resign()" << endl;
    string login = "testUser";
    Date date = Date("05.06.2021 19:00");
    setResponse("240 Login unsuccessful");
}

void Executor::modify() {
    cout << "In modify()" << endl;
    //data = login, old_date, new_date
    //if (Termin = findByStartDateAndLogin == nullptr) return error
    //update(Termin new Termin(data)) -> remove 7 add to schedules
    //add
    setResponse("104 Modification successful");
}

void Executor::check_my_termins() {
    cout << "In check_my_termins()" << endl;
    setResponse("240 Login unsuccessful");
}

void Executor::check_termins_by_instructor() {
    cout << "In check_termins_by_instructor()" << endl;
    setResponse("240 Login unsuccessful");
}
