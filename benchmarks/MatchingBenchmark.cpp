#include <benchmark/benchmark.h>
#include "../include/MatchingEngine.h"

static void BM_ProcessOrder(benchmark::State& state)
{
    MatchingEngine engine(10000);

    Order buyOrder(
        1,
        OrderType::LIMIT,
        TimeInForce::GTC,
        1,
        10,
        Side::BUY,
        100
    );
    Order sellOrder(
        2,
        OrderType::LIMIT,
        TimeInForce::GTC,
        1,
        20,
        Side::SELL,
        100 
    );
    for (auto _ : state)
    {
        engine.processOrder(buyOrder);
        engine.processOrder(sellOrder);
    }
}

BENCHMARK(BM_ProcessOrder);

BENCHMARK_MAIN();