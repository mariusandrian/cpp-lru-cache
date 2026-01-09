#include <catch2/catch_test_macros.hpp>

#include <cstdint>
#include <string>
#include <thread>
#include <iostream>
#include <chrono>
#include <barrier>

#include "lru.h"
#include "lru_naive_mutex.h"

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

TEST_CASE("should cause data race", "[race]")
{
    using namespace std::chrono_literals;
    LRUCache<std::string, std::string> lru(150);
    // std::cout << "thread " << std::this_thread::get_id() << '\n';
    // std::this_thread::sleep_for(2000ms);
    // std::cout << "my max: " << std::thread::hardware_concurrency() << '\n';
    auto onComplete = []()
    {
        std::cout << "completed" << '\n';
    };

    int threads = 100;
    std::barrier barrier(threads, onComplete);

    std::vector<std::thread> v;
    for (int i = 0; i < threads; ++i)
    {
        v.emplace_back([&](int idx)
                       {
                        auto tid = std::this_thread::get_id();
            barrier.arrive_and_wait();
            lru.set({std::to_string(idx), "something"}); }, i);
    }

    for (auto &t : v)
    {
        t.join();
    }

    REQUIRE(lru.size() == threads);
}

TEST_CASE("should not cause data race", "[race]")
{
    LRUCacheNaiveMutex<std::string, std::string> lru(150);
    auto onComplete = []()
    {
        std::cout << "completed" << '\n';
    };

    int threads = 100;
    std::barrier barrier(threads, onComplete);

    std::vector<std::thread> v;
    for (int i = 0; i < threads; ++i)
    {
        v.emplace_back([&](int idx)
                       {
                        auto tid = std::this_thread::get_id();
            barrier.arrive_and_wait();
            lru.set({std::to_string(idx), "something"}); }, i);
    }

    for (auto &t : v)
    {
        t.join();
    }

    REQUIRE(lru.size() == threads);
}