#include <catch2/catch.hpp>
#include <json/json.h>

using namespace json;

TEST_CASE("Creating JsonArray", "[JsonArray]") {
    SECTION("JsonArray can be default constructed") { JsonArray{}; }

    GIVEN("A default constructed JsonArray") {
        auto obj          = JsonArray{};
        auto someJsonVal  = JsonValue{JsonNumber{42}};
        auto someJsonVal2 = JsonValue{JsonNumber{12345}};
        THEN("obj.size() equals 0") { REQUIRE(obj.size() == 0u); }
        AND_WHEN("obj.push_back(someJsonVal) is called") {
            obj.push_back(someJsonVal);
            THEN("obj.size() equals 1") { REQUIRE(obj.size() == 1u); }

            AND_WHEN("obj.push_back(someJsonVal2) is called") {
                obj.push_back(someJsonVal2);
                THEN("obj.size() equals 2") { REQUIRE(obj.size() == 2u); }
            }
        }
    }
}

TEST_CASE("Accessing JsonArray entries", "[JsonArray]") {
    GIVEN("A JsonArray with one entry") {
        auto obj         = JsonArray{};
        auto someJsonVal = JsonValue{JsonNumber{42}};
        obj.push_back(someJsonVal);

        WHEN("obj.at(0) is called") {
            auto result = obj.at(0);
            THEN("the result equals the value stored") { REQUIRE(result == someJsonVal); }
        }
    }
}

TEST_CASE("Looping over member-attributes of JsonArray", "[JsonArray]") {
    GIVEN("A JsonArray with three members") {
        auto obj = JsonArray{};
        obj.push_back(JsonNumber{1});
        obj.push_back(JsonNumber{123});
        obj.push_back(JsonNumber{-200000});
        WHEN("we iterate over all entries of the array") {
            std::size_t numFoundEntries{0u};
            JsonValue   foundVal1, foundVal2, foundLastVal;

            for (const auto &entry : obj) {
                if (numFoundEntries == 0u) {
                    foundVal1 = entry;
                } else if (numFoundEntries == 1u) {
                    foundVal2 = entry;
                } else if (numFoundEntries == 2u) {
                    foundLastVal = entry;
                }
                numFoundEntries++;
            }
            THEN("all keys and values are found during iteration") {
                CHECK(numFoundEntries == 3u);
                CHECK(foundVal1 == JsonNumber{1});
                CHECK(foundVal2 == JsonNumber{123});
                CHECK(foundLastVal == JsonNumber{-200000});
            }
        }
    }
}