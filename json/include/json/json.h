#pragma once
#include <algorithm>
#include <cstddef>
#include <json/export.h>
#include <map>
#include <variant>

#define TODO                                                                                       \
    { throw; }

namespace json {

template <typename Derived> struct CRTP {
    constexpr auto self() const noexcept -> Derived const & {
        return *static_cast<Derived const *>(this);
    }
    constexpr auto self() noexcept -> Derived & { return *static_cast<Derived *>(this); }
};

template <typename Derived, typename ConversionTarget>
struct WithConversion : public CRTP<Derived> {
    constexpr operator ConversionTarget() const { return ConversionTarget{self()}; }
};

struct CompareForEqualityVisitor {
    template <typename T>
    constexpr auto operator()(T const &a, T const &b) const noexcept(noexcept(a == b)) -> bool {
        return a == b;
    }
    template <typename T, typename U>
    constexpr auto operator()(T const &a, U const &b) const noexcept -> bool {
        return false;
    }
};

class JsonNull;
class JsonBool;
class JsonNumber;
template <typename> class JsonString;

class JsonArray;
class JsonObject;
class JsonValue;
class JsonObjectIterator;

class JsonObject {
    std::map<std::string, JsonValue> m_dict;

  public:
    void insert(std::string const &key, JsonValue const &value);

    auto size() const -> std::size_t { return m_dict.size(); }

    auto at(std::string const &key) const -> JsonValue;

    auto begin() const -> JsonObjectIterator;
    auto end() const -> JsonObjectIterator;

    friend constexpr auto operator==(const JsonObject &a, const JsonObject &b) -> bool {
        return true;
    }

    friend constexpr auto operator!=(const JsonObject &a, const JsonObject &b) -> bool {
        return !(a == b);
    }
};

class JsonNumber {
    std::variant<int, double> m_value;

  public:
    JsonNumber(int value)
      : m_value{std::move(value)} {}

    JsonNumber(double value)
      : m_value{std::move(value)} {}

    friend constexpr auto operator==(const JsonNumber &a, const JsonNumber &b) -> bool {
        return std::visit(CompareForEqualityVisitor{}, a.m_value, b.m_value);
    }

    friend constexpr auto operator!=(const JsonNumber &a, const JsonNumber &b) -> bool {
        return !(a == b);
    }
};

class JsonBoolean : public WithConversion<JsonBoolean, JsonValue> {
    bool m_value;

  public:
    constexpr JsonBoolean()
      : m_value{false} {}

    constexpr explicit JsonBoolean(bool value)
      : m_value{std::move(value)} {}

    friend constexpr auto operator==(const JsonBoolean &a, const JsonBoolean &b) -> bool {
        return a.m_value == b.m_value;
    }

    friend constexpr auto operator!=(const JsonBoolean &a, const JsonBoolean &b) -> bool {
        return !(a == b);
    }

    constexpr operator bool() const { return m_value; }
};

class JsonArray {
  public:
    friend constexpr auto operator==(const JsonArray &a, const JsonArray &b) -> bool {
        return true;
    }
    friend constexpr auto operator!=(const JsonArray &a, const JsonArray &b) -> bool {
        return !(a == b);
    }
};

class JsonNull : public WithConversion<JsonNull, JsonValue> {
  public:
    constexpr JsonNull() = default;
    constexpr JsonNull(std::nullptr_t) {}

    friend constexpr auto operator==(const JsonNull &a, const JsonNull &b) -> bool { return true; }
    friend constexpr auto operator!=(const JsonNull &a, const JsonNull &b) -> bool {
        return !(a == b);
    }
};

template <typename> class JsonString;
struct JsonStringDynamicTag {};
struct JsonStringStaticTag {};

template <> class JsonString<JsonStringDynamicTag> {
    std::string m_value;

  public:
    JsonString() noexcept(std::is_nothrow_constructible_v<std::string>) = default;

    template <typename T>
    JsonString(T &&value)
      : m_value{std::forward<T>(value)} {}

    friend auto operator==(const JsonString &a, const JsonString &b) -> bool {
        return a.m_value == b.m_value;
    }

    friend auto operator!=(const JsonString &a, const JsonString &b) -> bool { return !(a == b); }
};

template <> class JsonString<JsonStringStaticTag> {
    char const *m_value;
    std::size_t m_size;

  public:
    constexpr JsonString() noexcept
      : m_value{nullptr}
      , m_size{0u} {}

    constexpr JsonString(char const *value, std::size_t size) noexcept
      : m_value{std::move(value)}
      , m_size{std::move(size)} {}

    template <std::size_t N>
    constexpr JsonString(char const (&literal)[N])
      : m_value{literal}
      , m_size{N} {}

    friend constexpr auto operator==(const JsonString &a, const JsonString &b) noexcept -> bool {
        if (a.m_size != b.m_size)
            return false;

        for (std::size_t i = 0u; i < a.m_size; ++i) {
            if (a.m_value[i] != b.m_value[i])
                return false;
        }
        return true;
    }

    friend constexpr auto operator!=(const JsonString &a, const JsonString &b) noexcept -> bool {
        return !(a == b);
    }

    constexpr operator bool() const noexcept { return m_value != nullptr; }
};

template <std::size_t N> JsonString(const char (&literal)[N])->JsonString<JsonStringStaticTag>;
JsonString(std::string)->JsonString<JsonStringDynamicTag>;
JsonString()->JsonString<JsonStringStaticTag>;

class JsonValue {

    std::variant<JsonNull, JsonBoolean, JsonNumber, JsonString<JsonStringStaticTag>,
                 JsonString<JsonStringDynamicTag>, JsonArray, JsonObject>
        m_value;

  public:
    constexpr JsonValue() noexcept
      : m_value{JsonNull{}} {};

    constexpr JsonValue(JsonNull) noexcept
      : m_value{JsonNull{}} {}

    constexpr JsonValue(JsonBoolean boolean)
      : m_value{std::move(boolean)} {}

    JsonValue(JsonNumber number)
      : m_value{std::move(number)} {}

    constexpr friend bool operator==(JsonValue const &a, JsonValue const &b) {
        if (a.m_value.index() != b.m_value.index())
            return false;

        return std::visit(CompareForEqualityVisitor{}, a.m_value, b.m_value);
    }

    constexpr friend bool operator!=(JsonValue const &a,
                                     JsonValue const &b) noexcept(noexcept(!(a == b))) {
        return !(a == b);
    }
};

void JsonObject::insert(std::string const &key, JsonValue const &value) {
    m_dict.insert(std::make_pair(key, value));
}

auto JsonObject::at(std::string const &key) const -> JsonValue { return m_dict.at(key); }

class JsonObjectIterator {
    std::map<std::string, JsonValue>::const_iterator m_it;

  public:
    JsonObjectIterator(std::map<std::string, JsonValue>::const_iterator it)
      : m_it{std::move(it)} {}

    JsonObjectIterator(JsonObjectIterator const &) = default;
    JsonObjectIterator(JsonObjectIterator &&)      = default;
    JsonObjectIterator &operator=(JsonObjectIterator const &) = default;
    JsonObjectIterator &operator=(JsonObjectIterator &&) = default;

    friend auto operator==(JsonObjectIterator const &a, JsonObjectIterator const &b) -> bool {
        return a.m_it == b.m_it;
    }

    friend auto operator!=(JsonObjectIterator const &a, JsonObjectIterator const &b) -> bool {
        return !(a == b);
    }

    auto operator++() -> JsonObjectIterator & {
        ++m_it;
        return *this;
    }

    auto operator++(int) -> JsonObjectIterator & {
        auto copy(*this);
        ++m_it;
        return copy;
    }

    auto operator*() const -> std::pair<std::string, JsonValue> { return *m_it; }
};

auto JsonObject::begin() const -> JsonObjectIterator { return JsonObjectIterator(m_dict.begin()); }
auto JsonObject::end() const -> JsonObjectIterator { return JsonObjectIterator(m_dict.end()); }

} // namespace json
