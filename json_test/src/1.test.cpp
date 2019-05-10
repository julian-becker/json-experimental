#include <catch2/catch.hpp>
#include <json/json.h>
#include <variant>

#define TODO { throw; }

namespace json {


	struct JsonObject {};
	struct JsonNumber {};
	class JsonBoolean {
		bool m_value;
	public:
		JsonBoolean(bool value) : m_value{ std::move(value) } {}
		friend auto operator == (const JsonBoolean& a, const JsonBoolean& b) {
			return a.m_value == b.m_value;
		}
	};
	struct JsonArray {};
	struct JsonNull {};
	struct JsonString {};


	struct JsonValue {
		std::variant<JsonNull, JsonBoolean, JsonNumber, JsonString, JsonArray, JsonObject> m_value;
		JsonValue& operator= (const JsonNull&) {
			//m_value = JsonNull{};
			return *this;
		}

		JsonValue& operator= (nullptr_t) {
			//m_value = JsonNull{};
			return *this;
		}

		JsonValue& operator= (JsonBoolean const& b) {
			m_value = b;
			return *this;
		}

		auto operator == (JsonNull const&) const -> bool {
			return true;
		}

		auto operator == (nullptr_t) const -> bool {
			return true;
		}

		auto operator == (JsonBoolean const& val) const -> bool {
			if (auto bval = std::get_if<JsonBoolean>(&m_value))
				return *bval == val;
			else
				return false;
		}

		template <typename Other>
		friend auto operator != (JsonValue const& val, Other const& other) -> bool {
			return !(val == other);
		}
	};
}

TEST_CASE("Dispatching on JsonValue type", "[api]") {
	using namespace json;
	GIVEN("a JsonValue") {
		JsonValue val;
		int vuiaeuiae = 0;
		WHEN("JsonNull{} is assigned to it") {
			val = JsonNull{};
			THEN("val compares equal to JsonNull") {
				REQUIRE(val == JsonNull{});
			}
		}

		WHEN("nullptr is assigned to it") {
			val = nullptr;
			THEN("val compares equal to JsonNull") {
				REQUIRE(val == JsonNull{});
			}
		}

		WHEN("JsonBoolean{true} is assigned to it") {
			val = JsonBoolean{ true };
			THEN("val compares equal to JsonBoolean{true}") {
				REQUIRE(val == JsonBoolean{ true });
			}
			THEN("val doesn't compare equal to JsonBoolean{false}") {
				REQUIRE(!(val == JsonBoolean{ false }));
			}
		}

		WHEN("JsonBoolean{false} is assigned to it") {
			val = JsonBoolean{ false };
			THEN("val compares equal to JsonBoolean{false}") {
				REQUIRE(val == JsonBoolean{ false });
			}
			THEN("val doesn't compare equal to JsonBoolean{true}") {
				REQUIRE(!(val == JsonBoolean{ true }));
			}
		}
	}
	
}
