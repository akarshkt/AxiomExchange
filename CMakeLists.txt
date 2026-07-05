cmake_minimum_required(VERSION 3.20)

project(ExchangeSimulator)

set(CMAKE_CXX_STANDARD 20)

find_package(benchmark REQUIRED)
find_package(GTest REQUIRED)

# ----------------------------
# Core Library
# ----------------------------

add_library(exchange_core

    src/Order.cpp
    src/Orderbook.cpp
    src/MatchingEngine.cpp
    src/Trade.cpp
    src/Logger.cpp
)

target_include_directories(exchange_core
    PUBLIC
    include
)

# ----------------------------
# Simulator
# ----------------------------

add_executable(simulator
    apps/sim.cpp
)

target_link_libraries(simulator
    PRIVATE
    exchange_core
)

# ----------------------------
# Benchmarks
# ----------------------------

add_executable(benchmark_matching

    benchmarks/MatchingBenchmark.cpp
)

target_link_libraries(
    benchmark_matching
    PRIVATE
    exchange_core
    benchmark::benchmark
)

# ----------------------------
# Tests
# ----------------------------

add_executable(exchange_tests

    tests/mainTest.cpp
    tests/OrderbookTest.cpp
    tests/TradeBookTest.cpp
    tests/TestUtils.cpp
)
target_include_directories(exchange_tests
    PUBLIC
    tests/utils
)
target_link_libraries(
    exchange_tests
    PRIVATE
    exchange_core
    GTest::gtest
)