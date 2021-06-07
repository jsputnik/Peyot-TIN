//Peyot
//Szymon Kisiel
//07.06.2021

//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../libs/catch.hpp"
#include "../server/database/DBManager.h"
#include <filesystem>

using namespace std;

TEST_CASE("Find user", "[Users database]") {
    DBManager dbManager("../tests/clients");
    SECTION("First user") {
        auto user = dbManager.find_user("login1");
        REQUIRE(user != nullptr);
        REQUIRE(user->getLogin() == "login1");
        REQUIRE(user->getHashedPassword() == "hash1");
        REQUIRE(user->getSalt() == "salt1");
    }
    SECTION("Second user") {
        auto user = dbManager.find_user("login2");
        REQUIRE(user != nullptr);
        REQUIRE(user->getLogin() == "login2");
        REQUIRE(user->getHashedPassword() == "hash2");
        REQUIRE(user->getSalt() == "salt2");
    }
    SECTION("Last user") {
        auto user = dbManager.find_user("login3");
        REQUIRE(user != nullptr);
        REQUIRE(user->getLogin() == "login3");
        REQUIRE(user->getHashedPassword() == "hash3");
        REQUIRE(user->getSalt() == "salt3");
    }
}

TEST_CASE("Find all users", "[Users database]") {
    DBManager dbManager("../tests/clients");
    auto users = dbManager.find_all();
    REQUIRE(users.size() == 3);
    REQUIRE(users[0].getLogin() == "login1");
    REQUIRE(users[1].getLogin() == "login2");
    REQUIRE(users[2].getLogin() == "login3");
    REQUIRE(users[0].getHashedPassword() == "hash1");
    REQUIRE(users[1].getHashedPassword() == "hash2");
    REQUIRE(users[2].getHashedPassword() == "hash3");
    REQUIRE(users[0].getSalt() == "salt1");
    REQUIRE(users[1].getSalt() == "salt2");
    REQUIRE(users[2].getSalt() == "salt3");
}

TEST_CASE("Add user", "[Users database]") {
    REQUIRE(std::filesystem::copy_file("../tests/clients", "../tests/temp", std::filesystem::copy_options::overwrite_existing));
    DBManager dbManager("../tests/temp");
    User newUser("new_login", "new_hash", "new_salt");
    dbManager.add_user(newUser);
    auto user = dbManager.find_user("new_login");
    REQUIRE(user != nullptr);
    REQUIRE(user->getLogin() == "new_login");
    REQUIRE(user->getHashedPassword() == "new_hash");
    REQUIRE(user->getSalt() == "new_salt");
}