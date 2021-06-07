//Peyot
//Szymon Kisiel
//07.06.2021

//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../libs/catch.hpp"
#include "../server/database/DBScheduleManager.h"
#include "../structures/Date.h"
#include <filesystem>

using namespace std;

TEST_CASE("Find date by client", "[Schedule database]") {
    DBScheduleManager dbManager("../tests/test_schedule");
    SECTION("Client in database") {
        auto dates = dbManager.find_by_client("klient3");
        REQUIRE(dates.size() == 2);
        REQUIRE(dates[0].get_start() == "16.05.2021 16:15");
        REQUIRE(dates[1].get_start() == "19.05.2021 16:15");
    }
    SECTION("Client not in database") {
        auto dates = dbManager.find_by_client("klient5");
        REQUIRE(dates.empty());
    }
}

TEST_CASE("Find date by instructor", "[Schedule database]") {
    DBScheduleManager dbManager("../tests/test_schedule");
    SECTION("Instructor in database") {
        auto dates = dbManager.find_by_instructor("instruktor3");
        REQUIRE(dates.size() == 2);
        REQUIRE(dates[0].get_start() == "16.05.2021 16:15");
        REQUIRE(dates[1].get_start() == "20.05.2021 16:15");
    }
    SECTION("Instructor not in database") {
        auto dates = dbManager.find_by_instructor("instruktor5");
        REQUIRE(dates.empty());
    }
}

TEST_CASE("Find date by instructor and client", "[Schedule database]") {
    DBScheduleManager dbManager("../tests/test_schedule");
    SECTION("Client and instructor in database") {
        auto dates = dbManager.find_by_instructor_and_client("instruktor1", "klient4");
        REQUIRE(dates.size() == 2);
        REQUIRE(dates[0].get_start() == "18.05.2021 16:15");
        REQUIRE(dates[1].get_start() == "22.05.2021 16:15");
    }
    SECTION("Wrong client") {
        auto dates = dbManager.find_by_instructor_and_client("instruktor1", "klient5");
        REQUIRE(dates.empty());
    }
    SECTION("Wrong instructor") {
        auto dates = dbManager.find_by_instructor_and_client("instruktor5", "klient4");
        REQUIRE(dates.empty());
    }
}

TEST_CASE("Find date", "[Schedule database]") {
    DBScheduleManager dbManager("../tests/test_schedule");
    SECTION("Client and instructor in database") {
        auto date = dbManager.find("instruktor1", "klient4", "22.05.2021 16:15");
        REQUIRE(date != nullptr);
        REQUIRE(date->get_end() == "22.05.2021 17:45");
    }
    SECTION("Wrong client") {
        auto date = dbManager.find("instruktor1", "klient5", "22.05.2021 16:15");
        REQUIRE(date == nullptr);
    }
    SECTION("Wrong instructor") {
        auto date = dbManager.find("instruktor5", "klient4", "22.05.2021 16:15");
        REQUIRE(date == nullptr);
    }
    SECTION("Wrong date") {
        auto date = dbManager.find("instruktor1", "klient4", "19.05.2021 16:15");
        REQUIRE(date == nullptr);
    }
}

TEST_CASE("Find date by instructor and date", "[Schedule database]") {
    DBScheduleManager dbManager("../tests/test_schedule");
    SECTION("Client and instructor in database") {
        auto date = dbManager.find_by_instructor_and_date("instruktor2",  "19.05.2021 16:15");
        REQUIRE(date != nullptr);
        REQUIRE(date->get_client() == "klient3");
    }
    SECTION("Wrong instructor") {
        auto date = dbManager.find_by_instructor_and_date("instruktor5",  "19.05.2021 16:15");
        REQUIRE(date == nullptr);
    }
    SECTION("Wrong date") {
        auto date = dbManager.find_by_instructor_and_date("instruktor2",  "20.05.2021 16:15");
        REQUIRE(date == nullptr);
    }
}

TEST_CASE("Find all dates", "[Schedule database]") {
    DBScheduleManager dbManager("../tests/test_schedule");
    auto dates = dbManager.find_all();
    REQUIRE(dates.size() == 9);
    SECTION("First date") {
        REQUIRE(dates[0].get_start() == "14.05.2021 16:15");
        REQUIRE(dates[0].get_end() == "14.05.2021 17:45");
        REQUIRE(dates[0].get_client() == "klient1");
        REQUIRE(dates[0].get_instructor() == "instruktor1");
    }
    SECTION("Middle date") {
        REQUIRE(dates[5].get_start() == "19.05.2021 16:15");
        REQUIRE(dates[5].get_end() == "19.05.2021 17:45");
        REQUIRE(dates[5].get_client() == "klient3");
        REQUIRE(dates[5].get_instructor() == "instruktor2");
    }
    SECTION("Last date") {
        REQUIRE(dates[8].get_start() == "22.05.2021 16:15");
        REQUIRE(dates[8].get_end() == "22.05.2021 17:45");
        REQUIRE(dates[8].get_client() == "klient4");
        REQUIRE(dates[8].get_instructor() == "instruktor1");
    }
}

TEST_CASE("Add date", "[Schedule database]") {
    REQUIRE(std::filesystem::copy_file("../tests/test_schedule", "../tests/temp", std::filesystem::copy_options::overwrite_existing));
    DBScheduleManager dbManager("../tests/temp");
    REQUIRE(dbManager.find("instruktor5", "klient5", "01.06.2021 10:15") == nullptr);
    Date newDate("01.06.2021 10:15", "01.06.2021 11:45", "instruktor5", "klient5");
    dbManager.add_date(newDate);
    REQUIRE(dbManager.find("instruktor5", "klient5", "01.06.2021 10:15") != nullptr);
}

TEST_CASE("Modify date", "[Schedule database]") {
    REQUIRE(std::filesystem::copy_file("../tests/test_schedule", "../tests/temp", std::filesystem::copy_options::overwrite_existing));
    DBScheduleManager dbManager("../tests/temp");
    auto date = dbManager.find_by_instructor_and_date("instruktor2",  "19.05.2021 16:15");
    REQUIRE(date != nullptr);
    REQUIRE(date->get_client() == "klient3");
    REQUIRE(date->get_end() == "19.05.2021 17:45");

    Date newDate("19.05.2021 16:15", "19.05.2021 16:45", "instruktor2", "klient5");
    dbManager.modify_date("instruktor2", "klient3", "19.05.2021 16:15", newDate);

    date = dbManager.find_by_instructor_and_date("instruktor2",  "19.05.2021 16:15");
    REQUIRE(date != nullptr);
    REQUIRE(date->get_client() == "klient5");
    REQUIRE(date->get_end() == "19.05.2021 16:45");
}

TEST_CASE("Delete date", "[Schedule database]") {
    REQUIRE(std::filesystem::copy_file("../tests/test_schedule", "../tests/temp", std::filesystem::copy_options::overwrite_existing));
    DBScheduleManager dbManager("../tests/temp");
    auto date = dbManager.find_by_instructor_and_date("instruktor2",  "19.05.2021 16:15");
    REQUIRE(date != nullptr);
    REQUIRE(date->get_client() == "klient3");
    REQUIRE(date->get_end() == "19.05.2021 17:45");

    dbManager.delete_date("instruktor2", "klient3", "19.05.2021 16:15");

    date = dbManager.find_by_instructor_and_date("instruktor2",  "19.05.2021 16:15");
    REQUIRE(date == nullptr);
}
