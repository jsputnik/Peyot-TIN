//30.05.2021

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../libs/catch.hpp"

TEST_CASE( "Always true" ) {
    REQUIRE(1 == 1);
}