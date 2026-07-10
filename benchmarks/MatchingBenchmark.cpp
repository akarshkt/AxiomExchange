#include <benchmark/benchmark.h>
#include "../include/MatchingEngine.h"

static void BM_ProcessOrder(benchmark::State& state)
{
    MatchingEngine engine(10000);

    Order order(
        1,
        OrderType::LIMIT,
        TimeInForce::GTC,
        1,
        10,
        Side::BUY,
        100
    );

    for (auto _ : state)
    {
        engine.processOrder(order);
    }
}

BENCHMARK(BM_ProcessOrder);

BENCHMARK_MAIN();