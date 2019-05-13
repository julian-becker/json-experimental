#include <catch2/catch.hpp>
#include <json/json.h>

using namespace json;

TEST_CASE("Creating JsonBoolean instance", "[JsonBoolean]") {
    GIVEN("A default constructed JsonBoolean") {
        JsonBoolean value{};
        WHEN("converted to bool") {
            bool result = value;
            THEN("the result is false") { REQUIRE_FALSE(result); }
        }
        WHEN("compared to a JsonBoolean{false}") {
            JsonBoolean other{false};
            THEN("the result is true") {
                REQUIRE(value == other);
                REQUIRE_FALSE(value != other);
            }
        }
        WHEN("compared to a JsonBoolean{true}") {
            JsonBoolean other{true};
            THEN("the result is false") {
                REQUIRE(value != other);
                REQUIRE_FALSE(value == other);
            }
        }
    }
    GIVEN("Two identical JsonBoolean values") {
        JsonBoolean valueTrue{true}, valueTrue2{true};
        WHEN("when they are compared") {
            bool result = (valueTrue == valueTrue2);
            THEN("the result is true") { REQUIRE(result); }
        }
    }
    GIVEN("Two different JsonBoolean values") {
        JsonBoolean valueTrue{true}, valueFalse{false};
        WHEN("when they are compared") {
            bool result = (valueTrue == valueFalse);
            THEN("the result is false") { REQUIRE_FALSE(result); }
        }
    }
}