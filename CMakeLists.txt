cmake_minimum_required(VERSION 3.23)

project(LruCache)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(LruCache)

target_sources(LruCache
  PRIVATE
    lru_main.cc
)

target_compile_options(LruCache
  PRIVATE
    -Wall
    -Wextra
)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.12.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests test.cc)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)