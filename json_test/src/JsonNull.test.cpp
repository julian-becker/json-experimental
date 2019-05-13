#include <catch2/catch.hpp>
#include <json/json.h>

using namespace json;

TEST_CASE("Creating JsonNull instance", "[JsonNull]") {
    SECTION("Default construction") { JsonNull value{}; }

    SECTION("Construction from nullptr") { JsonNull value = nullptr; }
}
