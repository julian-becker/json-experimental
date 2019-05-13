#include <catch2/catch.hpp>
#include <json/json.h>

using namespace json;

TEST_CASE("Creating a JsonNumber instance", "[JsonNumber]") {
    GIVEN("An integer") {
        int some_value = 1234567;
        WHEN("A JsonNumber is created from this int") {
            auto instance = JsonNumber{some_value};
            THEN("the instance compares equal to the int it was created from") {
                REQUIRE(instance == some_value);
            }
        }
    }
}

TEST_CASE("Comparing JsonNumber instances", "[JsonNumber]") {
    GIVEN("two distinct integers") {
        int int1{123}, int2{1234};
        WHEN("creating JsonNumber instances for these integers") {
            auto jsonNum1 = JsonNumber{int1};
            auto jsonNum2 = JsonNumber{int2};
            THEN("the JsonNumber instances are distinct as well") {
                REQUIRE(jsonNum1 != jsonNum2);
                REQUIRE_FALSE(jsonNum1 == jsonNum2);
            }
        }
    }

    GIVEN("two identical integers") {
        int int1{123};
        int int2{int1};
        WHEN("creating JsonNumber instances for these integers") {
            auto jsonNum1 = JsonNumber{int1};
            auto jsonNum2 = JsonNumber{int2};
            THEN("the JsonNumber instances are identical as well") {
                REQUIRE(jsonNum1 == jsonNum2);
                REQUIRE_FALSE(jsonNum1 != jsonNum2);
            }
        }
    }

    GIVEN("two distinct doubles") {
        double double1{123.1}, double2{1.231};
        WHEN("creating JsonNumber instances for these doubles") {
            auto jsonNum1 = JsonNumber{double1};
            auto jsonNum2 = JsonNumber{double2};
            THEN("the JsonNumber instances are distinct as well") {
                REQUIRE(jsonNum1 != jsonNum2);
                REQUIRE_FALSE(jsonNum1 == jsonNum2);
            }
        }
    }
}
