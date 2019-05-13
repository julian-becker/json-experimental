#include <catch2/catch.hpp>
#include <json/json.h>

using namespace json;

TEST_CASE("Creating a JsonString instance", "[JsonString]") {
    SECTION("Default construction") {
        JsonString{};
        static_assert(JsonString{} == JsonString{});
        static_assert(!(JsonString{} != JsonString{}));
    }

    SECTION("Construction from string-literal at compile-time") {

        static_assert(JsonString{"123"} == JsonString{"123"});
        static_assert(!(JsonString{"123"} != JsonString{"123"}));

        static_assert(JsonString{"321"} != JsonString{"123"});
        static_assert(!(JsonString{"321"} == JsonString{"123"}));
    }

    SECTION("Constructing from literal string") {
        GIVEN("A string literal") {

            auto &&literal = "some literal string";
            WHEN("Two instances are created from this literal") {
                JsonString s1{literal};
                JsonString s2{literal};
                THEN("they compare equal") {
                    REQUIRE(s1 == s2);
                    REQUIRE_FALSE(s1 != s2);
                }
            }
        }
    }
}
