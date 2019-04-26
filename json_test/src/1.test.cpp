#include <catch2/catch.hpp>
#include <json/json.h>

#define TODO { throw; }

namespace json {

	class JsonConsumerBuilder {

	};

	template <typename T>
	struct JsonVisitor {
		using result_type = T;
	};

	struct JsonObject {};
	struct JsonNumber {};
	struct JsonBoolean {};
	struct JsonNull {};
	struct JsonString {};


	struct Json {
		template <typename T, typename Fn>
		auto on(Fn&& fn) {
			if()
			return 
		}
	};


}


namespace Test0
{
	using namespace json;
	TEST_CASE("json_api_foobar returns the ultimate result", "[json_api_foobar]") {
		JsonObject obj;

	}
}

namespace Test1
{
	TEST_CASE("second test", "[json_api_foobar]") {
		REQUIRE(42 == json_api());

	}
}
