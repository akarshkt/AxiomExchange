cmake_minimum_required(VERSION 3.20)

project(ExchangeSimulator)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)
# add_executable(exchange

# 	src/sim.cpp
# )
add_executable(simulator
    src/sim.cpp
    src/MatchingEngine.cpp
    src/Order.cpp
    src/Orderbook.cpp
)