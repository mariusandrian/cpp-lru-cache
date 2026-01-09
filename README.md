# LRU Cache

The cache is made using templates and modern C++17 features such as `std::optional`. Unit tests are done using Catch2 for its simple interface and setup. Project is built with CMake.

Source for the cache class is all inside `lru.h`.

## Build
```
cmake -B build
cmake --build build
```

## Run
```
./build/LruCache
./build/tests
```