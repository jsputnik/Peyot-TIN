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
    //if request == login -> loginUser
    //if request == register -> registerUser
    //...
    setResponse("UNASSIGNED RESPONSE");
}

void Executor::loginUser() {
    //for now hardcoded
    string login = request->getUser().getLogin();
    string password = request->getUser().getHashedPassword();
//    string login = "mkwerc";
//    string password = "passwd";
    DBManager dbManager("../server/database/clients");
    std::unique_ptr<User> user = dbManager.find_user(login);
    if (user == nullptr) {
        setResponse("210 Login unsuccessful");
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
    setResponse("210 Login unsuccessful");
}

void Executor::registerUser() {
    //for now hardcoded
    string login = "testuser";
    string password = "testpasswd";
    unsigned char salt[security_manager.getNotEncodedSaltLength()];
    unsigned char encoded_salt[security_manager.getEncodedSaltLength()];
    security_manager.generate_salt(encoded_salt, salt, security_manager.getNotEncodedSaltLength()); //encoded_salt_length
    unsigned char hash[SHA512_DIGEST_LENGTH];
    unsigned char encoded_hash[4*(SHA512_DIGEST_LENGTH+2)/3];
    security_manager.hash_password(SecurityManager::merge_salt_with_password(encoded_salt, security_manager.getEncodedSaltLength(), password), hash, encoded_hash, SHA512_DIGEST_LENGTH);

    DBManager dbManager("../server/database/clients");
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
