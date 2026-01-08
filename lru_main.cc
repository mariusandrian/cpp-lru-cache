#include <iostream>

#include "cassert"

#include "lru.h"

int main()
{
    LRUCache<std::string, std::string> lru(2);

    auto [it, ok] = lru.set({"hello", "world"});
    assert(ok);

    auto val = lru.find("hello");
    assert(val.has_value());
    assert(val.value() == "world");

    std::cout << "value is " << val.value() << "\n";

    lru.set({"two", "set"});
    lru.set({"three", "time"});

    val = lru.find("hello");
    assert(!val.has_value());

    // Three should be at the top now.
    val = lru.find("three");
    assert(val.value() == "time");
    lru.set({"four", "kay"});
    // Four at the top, three should still remain.
    val = lru.find("three");
    assert(val.value() == "time");
}