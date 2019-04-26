#include <catch2/catch.hpp>
#include <json/json.h>

TEST_CASE("json_api_foobar returns the ultimate result", "[json_api_foobar]") {
	REQUIRE(42 == json_api());
}
