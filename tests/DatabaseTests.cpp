//Peyot
//Szymon Kisiel
//07.06.2021

//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../libs/catch.hpp"
#include "../server/database/DBManager.h"

using namespace std;

TEST_CASE( "DBTest" ) {
    DBManager dbManager("clients");
    REQUIRE(1 == 1);
//    auto user = dbManager.find_user("bderk");
//    REQUIRE(user->getLogin() == "bderk");
//    REQUIRE(user->getHashedPassword() == "");
//    REQUIRE(user->getSalt() == "");
}