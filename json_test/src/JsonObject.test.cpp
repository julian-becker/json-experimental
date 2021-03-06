#include <catch2/catch.hpp>
#include <json/json.h>

using namespace json;

TEST_CASE("Creating JsonObject", "[JsonObject]") {
    SECTION("JsonObject can be default constructed") { JsonObject{}; }

    GIVEN("A default constructed JsonObject") {
        auto obj          = JsonObject{};
        auto someJsonVal  = JsonValue{JsonNumber{42}};
        auto someJsonVal2 = JsonValue{JsonNumber{12345}};
        THEN("obj.size() equals 0") { REQUIRE(obj.size() == 0u); }
        AND_WHEN("obj.insert(\"key\", someJsonVal) is called") {
            obj.insert("key", someJsonVal);
            THEN("obj.size() equals 1") { REQUIRE(obj.size() == 1u); }

            AND_WHEN("obj.insert(\"key2\", someJsonVal) is called") {
                obj.insert("key2", someJsonVal);
                THEN("obj.size() equals 2") { REQUIRE(obj.size() == 2u); }

                AND_WHEN("obj.insert(\"key2\", someJsonVal2) is called again with same key") {
                    obj.insert("key2", someJsonVal2);
                    THEN("obj.size() still equals 2") { REQUIRE(obj.size() == 2u); }
                }
            }
        }
    }
}

TEST_CASE("Accessing JsonObject entries", "[JsonObject]") {
    GIVEN("A JsonObject with one entry") {
        auto obj         = JsonObject{};
        auto someJsonVal = JsonValue{JsonNumber{42}};
        obj.insert("key1", someJsonVal);

        WHEN("obj.at(\"key1\") is called") {
            auto result = obj.at("key1");
            THEN("the result equals the value stored with that key") {
                REQUIRE(result == someJsonVal);
            }
        }
    }
}

TEST_CASE("Looping over member-attributes of JsonObject", "[JsonObject]") {
    GIVEN("A JsonObject with three members") {
        auto obj = JsonObject{};
        obj.insert("key1", JsonNumber{1});
        obj.insert("key2", JsonNumber{123});
        obj.insert("last key", JsonNumber{-200000});
        WHEN("we iterate over all entries of the object") {
            bool      foundKey1 = false, foundKey2 = false, foundLastkey = false;
            JsonValue foundVal1, foundVal2, foundLastVal;

            for (const auto &entry : obj) {
                if (entry.first == "key1") {
                    foundKey1 = true;
                    foundVal1 = entry.second;
                } else if (entry.first == "key2") {
                    foundKey2 = true;
                    foundVal2 = entry.second;
                } else if (entry.first == "last key") {
                    foundLastkey = true;
                    foundLastVal = entry.second;
                }
            }
            THEN("all keys and values are found during iteration") {
                CHECK(foundKey1);
                CHECK(foundVal1 == JsonNumber{1});
                CHECK(foundKey2);
                CHECK(foundVal2 == JsonNumber{123});
                CHECK(foundLastkey);
                CHECK(foundLastVal == JsonNumber{-200000});
            }
        }
    }
}