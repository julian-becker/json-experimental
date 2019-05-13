#include <catch2/catch.hpp>
#include <json/json.h>

using namespace json;

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
