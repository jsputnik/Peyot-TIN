//29.05.2021

#include "Executor.h"
#include "database/DBManager.h"
#include <iostream>
#include <openssl/sha.h>

using namespace std;

Executor::Executor(string request) {
    this->request = request;
}

//return response ?
void Executor::execute() {
    if (request == "quit") {
        setResponse("150 Logged out");
        return;
    }
    setResponse("UNASSIGNED RESPONSE");
    //if msg_rcvd == login -> loginUser
    //if msg_rcvd == register -> registerUser
    //...
    registerUser();
}

void Executor::loginUser() {
    //for now hardcoded
    string login = "marek";
    string password = "passwd";
    DBManager dbManager("../server/database/clients");
    //TODO: findSalt(login), findHashedPasswd(login)
    //salt = find salt
    //hashed passwd = find hashed_passwd
}

void Executor::registerUser() {
    //for now hardcoded
    string login = "testuser";
    string password = "testpasswd";

    int not_encoded_salt_length = 16;
    int encoded_salt_length = 4*(not_encoded_salt_length+2)/3; //
    unsigned char salt[not_encoded_salt_length];
    unsigned char encoded_salt[encoded_salt_length];
    security_manager.generate_salt(encoded_salt, salt, not_encoded_salt_length); //encoded_salt_length
//    cout << "Encoded salt: " << endl;
//    for (unsigned int i = 0; i < encoded_salt_length; ++i) {
//        cout << encoded_salt[i];
//    }
//    cout << endl;
    unsigned char hash[SHA512_DIGEST_LENGTH];
    unsigned char encoded_hash[4*(SHA512_DIGEST_LENGTH+2)/3]; //86
//    unsigned char salt[not_encoded_salt_length];
//    security_manager.decode(salt, encoded_salt, encoded_salt_length);
//    cout << "Decoded salt: " << endl;
//    for (unsigned int i = 0; i < not_encoded_salt_length; ++i) {
//        cout << salt[i];
//    }
//    cout << endl;
    security_manager.hash_password(SecurityManager::merge_salt_with_password(encoded_salt, encoded_salt_length, password), hash, encoded_hash, SHA512_DIGEST_LENGTH);

    DBManager dbManager("../server/database/clients");
    //cast unsigned char to char
    string hash_string = reinterpret_cast<char*>(encoded_hash);
    string salt_string = reinterpret_cast<char*>(encoded_salt);
    dbManager.add_user(User(login, hash_string, salt_string));
}

void Executor::setResponse(const string &response) {
    Executor::response = response;
}

const string &Executor::getResponse() const {
    return response;
}
