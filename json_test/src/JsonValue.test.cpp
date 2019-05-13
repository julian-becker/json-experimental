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

    SECTION("Construction from nullptr") {
        GIVEN("A JsonValue{nullptr}") {
            JsonValue val{nullptr};
            WHEN("Compared against a JsonNull object") {
                auto equality   = (val == JsonNull{});
                auto inequality = (val != JsonNull{});
                THEN("it compares equal") {
                    REQUIRE(equality);
                    REQUIRE_FALSE(inequality);
                }
            }
        }
    }

    SECTION("Comparison against nullptr") {
        GIVEN("a JsonValue{nullptr}") {
            JsonValue val{nullptr};
            WHEN("Compared against a nullptr object") {
                auto equality   = (val == nullptr);
                auto inequality = (val != nullptr);
                THEN("it compares equal") {
                    REQUIRE(equality);
                    REQUIRE_FALSE(inequality);
                }
            }
        }
    }

    SECTION("Construction from bool") {
        GIVEN("A JsonValue{true}") {
            JsonValue val{true};
            WHEN("Compared against a JsonBoolean{true} object") {
                auto equality   = (val == JsonBoolean{true});
                auto inequality = (val != JsonBoolean{true});
                THEN("it compares equal") {
                    REQUIRE(equality);
                    REQUIRE_FALSE(inequality);
                }
            }
        }
        GIVEN("A JsonValue{false}") {
            JsonValue val{false};
            WHEN("Compared against a JsonBoolean{false} object") {
                auto equality   = (val == JsonBoolean{false});
                auto inequality = (val != JsonBoolean{false});
                THEN("it compares equal") {
                    REQUIRE(equality);
                    REQUIRE_FALSE(inequality);
                }
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
