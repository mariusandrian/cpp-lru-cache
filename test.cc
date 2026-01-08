#include <catch2/catch_test_macros.hpp>

#include <cstdint>
#include <string>

#include "lru.h"

TEST_CASE("should handle simple cases", "[lru]")
{
    LRUCache<std::string, std::string> lru(2);
    SECTION("entry is saved")
    {
        lru.set({"hello", "world"});
        auto res = lru.find("hello");
        REQUIRE(res.has_value() == true);
        REQUIRE(res.value() == "world");
    }

    SECTION("evicts entry when capacity reached")
    {
        lru.set({"hello", "world"});
        lru.set({"two", "set"});
        lru.set({"three", "pods"});

        // hello is evicted.
        auto first = lru.find("hello");
        REQUIRE(first.has_value() == false);

        auto second = lru.find("three");
        REQUIRE(second.has_value() == true);
        REQUIRE(second.value() == "pods");
    }

    SECTION("updates order on find and evicts")
    {
        lru.set({"hello", "world"});
        lru.set({"two", "set"});

        lru.find("hello");

        lru.set({"three", "pods"});

        // two is evicted.
        auto actual = lru.find("two");
        REQUIRE(actual.has_value() == false);
    }
}