//
// Created by ilya on 07.06.2021.
//
//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../libs/catch.hpp"
#include <string>
#include "../parser/Parser.h"
using namespace std;

TEST_CASE( "Parse Book Request") {
    string message = "book vdiesel 07.06.2021 07:00";
    Parser parser(message);
    auto bookRequest = parser.parse_request();
    REQUIRE(bookRequest->getType() == RequestType::BOOK);
    REQUIRE(bookRequest->getKeyword() == "book");
    REQUIRE(bookRequest->getLogin() == "vdiesel");
    REQUIRE(bookRequest->getDate() == "07.06.2021 07:00");

}

TEST_CASE("Parse Resign Request"){
    string message = "resign vdiesel 07.06.2021 07:00";
    Parser parser(message);
    auto resignRequest = parser.parse_request();
    REQUIRE(resignRequest->getType() == RequestType::RESIGN);
    REQUIRE(resignRequest->getKeyword() == "resign");
    REQUIRE(resignRequest->getLogin() == "vdiesel");
    REQUIRE(resignRequest->getDate() == "07.06.2021 07:00");
}

TEST_CASE("Parse Check My Termins Request"){
    string message = "check -mytermins";
    Parser parser(message);
    auto checkRequest = parser.parse_request();
    REQUIRE(checkRequest->getType() == RequestType::CHECKMYTERMINS);
    REQUIRE(checkRequest->getKeyword() == "check");
    REQUIRE(checkRequest->getFlag() == "mytermins");
}

TEST_CASE("Parse Check Instructors Request"){
    string message = "check -instructors";
    Parser parser(message);
    auto checkRequest = parser.parse_request();
    REQUIRE(checkRequest->getType() == RequestType::CHECKINSTRUCTORS);
    REQUIRE(checkRequest->getKeyword() == "check");
    REQUIRE(checkRequest->getFlag() == "instructors");
}

TEST_CASE("Parse Check Termins By Instructor Request"){
    string message = "check -instermins karol";
    Parser parser(message);
    auto checkRequest = parser.parse_request();
    REQUIRE(checkRequest->getType() == RequestType::CHECKTERMINSBYTRUCTOR);
    REQUIRE(checkRequest->getKeyword() == "check");
    REQUIRE(checkRequest->getFlag() == "instermins");
    REQUIRE(checkRequest->getLogin() == "karol");
}

TEST_CASE("Parse Modify Request"){
    string message = "modify wojtek 01.01.2021 00:00 02.01.2021 00:00";
    Parser parser(message);
    auto modifyRequest = parser.parse_request();
    REQUIRE(modifyRequest->getType() == RequestType::MODIFY);
    REQUIRE(modifyRequest->getKeyword() == "modify");
    REQUIRE(modifyRequest->getLogin() == "wojtek");
    REQUIRE(modifyRequest->getOldDate() == "01.01.2021 00:00");
    REQUIRE(modifyRequest->getNewDate() == "02.01.2021 00:00");
}

TEST_CASE("Parse Login Request"){
    string message = "login adam qwerty";
    Parser parser(message);
    auto loginRequest = parser.parse_request();
    REQUIRE(loginRequest->getType() == RequestType::LOGIN);
    REQUIRE(loginRequest->getKeyword() == "login");
    REQUIRE(loginRequest->getLogin() == "adam");
    REQUIRE(loginRequest->getPassword() == "qwerty");
}

TEST_CASE("Parse Quit Request"){
    string message = "quit";
    Parser parser(message);
    auto quitRequest = parser.parse_request();
    REQUIRE(quitRequest->getType() == RequestType::QUIT);
    REQUIRE(quitRequest->getKeyword() == "quit");
}

TEST_CASE("Parse Register Instructor Request"){
    string message = "register -i janusz 123";
    Parser parser(message);
    auto registerRequest = parser.parse_request();
    REQUIRE(registerRequest->getType() == RequestType::REGISTER);
    REQUIRE(registerRequest->getKeyword() == "register");
    REQUIRE(registerRequest->getFlag() == "i");
    REQUIRE(registerRequest->getLogin() == "janusz");
    REQUIRE(registerRequest->getPassword() == "123");
}

TEST_CASE("Parse Register Client Request"){
    string message = "register -c tomek 123";
    Parser parser(message);
    auto registerRequest = parser.parse_request();
    REQUIRE(registerRequest->getType() == RequestType::REGISTER);
    REQUIRE(registerRequest->getKeyword() == "register");
    REQUIRE(registerRequest->getFlag() == "c");
    REQUIRE(registerRequest->getLogin() == "tomek");
    REQUIRE(registerRequest->getPassword() == "123");
}

TEST_CASE("Parse Set Schedule Request") {
    string message = "setschedule 12.07.2021 18:15";
    Parser parser(message);
    auto setScheduleRequest = parser.parse_request();
    REQUIRE(setScheduleRequest->getType() == RequestType::SETSCHEDULE);
    REQUIRE(setScheduleRequest->getKeyword() == "setschedule");
    REQUIRE(setScheduleRequest->getDate() == "12.07.2021 18:15");
}

TEST_CASE("Parse Response 1xx") {
    string message = "100 Login successful";
    Parser parser(message);
    auto response = parser.parse_response();
    REQUIRE(response->getFirst() == 1);
    REQUIRE(response->getSecond() == 0);
    REQUIRE(response->getThird() == 0);
    REQUIRE(response->getMessage() == "Login successful");
}

TEST_CASE("Parse Response 2xx") {
    string message = "214 Modification unsuccessful: date doesn't exist";
    Parser parser(message);
    auto response = parser.parse_response();
    REQUIRE(response->getFirst() == 2);
    REQUIRE(response->getSecond() == 1);
    REQUIRE(response->getThird() == 4);
    REQUIRE(response->getMessage() == "Modification unsuccessful: date doesn't exist");
}

TEST_CASE("Parse Response 3xx") {
    string message = "313 Resign unsuccessful: couldn't resign";
    Parser parser(message);
    auto response = parser.parse_response();
    REQUIRE(response->getFirst() == 3);
    REQUIRE(response->getSecond() == 1);
    REQUIRE(response->getThird() == 3);
    REQUIRE(response->getMessage() == "Resign unsuccessful: couldn't resign");
}

TEST_CASE("Parse Response 4xx") {
    string message = "430 Timed out";
    Parser parser(message);
    auto response = parser.parse_response();
    REQUIRE(response->getFirst() == 4);
    REQUIRE(response->getSecond() == 3);
    REQUIRE(response->getThird() == 0);
    REQUIRE(response->getMessage() == "Timed out");
}



