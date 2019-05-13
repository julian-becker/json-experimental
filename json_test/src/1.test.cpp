#include <catch2/catch.hpp>
#include <json/json.h>

using namespace json;

TEST_CASE("Creating JsonNull instance", "[JsonNull]") {
    SECTION("Default construction") { JsonNull value{}; }

    SECTION("Construction from nullptr") { JsonNull value = nullptr; }
}

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

TEST_CASE("Creating a JsonValue instance", "[JsonValue]") {
    SECTION("Default Construction") {
        JsonValue val{};
        WHEN("Compared against a JsonNull object") {
            auto equality   = (val == JsonNull{});
            auto inequality = (val != JsonNull{});
            THEN("it compares equal") {
                REQUIRE(equality);
                REQUIRE_FALSE(inequality);
            }
        }
    }

    SECTION("Construction from JsonNull") {
        JsonValue val{JsonNull{}};
        WHEN("Compared against a JsonNull object") {
            auto equality   = (val == JsonNull{});
            auto inequality = (val != JsonNull{});
            THEN("it compares equal") {
                REQUIRE(equality);
                REQUIRE_FALSE(inequality);
            }
        }
    }

    SECTION("Construction from JsonBoolean") {
        GIVEN("Two JsonValue instances constructed from different JsonBoolean values") {
            JsonValue valueTrue{JsonBoolean{true}}, valueFalse{JsonBoolean{false}};

            WHEN("valueTrue compared against a JsonNull object") {
                auto equality   = (valueTrue == JsonNull{});
                auto inequality = (valueTrue != JsonNull{});
                THEN("it compares unequal") {
                    REQUIRE(inequality);
                    REQUIRE_FALSE(equality);
                }
            }

            WHEN("valueFalse compared against a JsonNull object") {
                auto equality   = (valueTrue == JsonNull{});
                auto inequality = (valueTrue != JsonNull{});
                THEN("it compares unequal") {
                    REQUIRE(inequality);
                    REQUIRE_FALSE(equality);
                }
            }

            WHEN("Comparing valueFalse against valueTrue") {
                auto equality   = (valueTrue == valueFalse);
                auto inequality = (valueTrue != valueFalse);
                THEN("they compare unequal") {
                    REQUIRE(inequality);
                    REQUIRE_FALSE(equality);
                }
            }
        }
    }
}

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