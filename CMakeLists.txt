cmake_minimum_required(VERSION 3.20)


project(ExchangeSimulator)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

find_package(benchmark REQUIRED)

# Create the library
add_library(exchange_core
    src/MatchingEngine.cpp
    src/Order.cpp
    src/Orderbook.cpp
)

# Simulator executable
add_executable(simulator
    src/sim.cpp
)

target_link_libraries(simulator
    PRIVATE
    exchange_core
)

# Benchmark executable
add_executable(benchmark_matching
    benchmarks/MatchingBenchmark.cpp
)

target_link_libraries(benchmark_matching
    PRIVATE
    exchange_core
    benchmark::benchmark
)