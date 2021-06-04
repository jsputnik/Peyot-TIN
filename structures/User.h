//26.05.2021

#ifndef DATABASE_USER_H
#define DATABASE_USER_H

#include <string>

class User {
    std::string login;
    std::string hashed_password;
    std::string salt;
public:
    User(std::string login, std::string hashed_passwd, std::string salt) :
        login(login),
        hashed_password(hashed_passwd),
        salt(salt) {
    }

    const std::string &getLogin() const {
        return login;
    }

    const std::string &getHashedPassword() const {
        return hashed_password;
    }

    const std::string &getSalt() const {
        return salt;
    }

//    unsigned char *getHashedPassword() const {
//        return hashed_password;
//    }
//
//    unsigned char *getSalt() const {
//        return salt;
//    }
};


#endif //DATABASE_USER_H
