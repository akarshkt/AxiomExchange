# Performance Journal

07/12/2026 - 7:00pm

## Baseline

----------------------------------------------------------
Benchmark                Time             CPU   Iterations
----------------------------------------------------------
BM_ProcessOrder     107485 ns       106578 ns         6717

Time : 107 µs


This is the benchmark of entire exchange to process two orders, 1 buy and 1 sell which completely pairs up.

Notes:

CSV logging is enabled.
Cancellation of order not optimised.

## Optimization 1

Changes:

CSV logging disabled.

----------------------------------------------------------
Benchmark                Time             CPU   Iterations
----------------------------------------------------------
BM_ProcessOrder        315 ns          315 ns      1806391

Time : 0.315 µs

Huge Improvement after logging disabled.
107 µs -> 0.315 µs

Improvement = 356x

## Optimization 2

----------------------------------------------------------
Benchmark                Time             CPU   Iterations
----------------------------------------------------------
BM_ProcessOrder        290 ns          290 ns      1883523

Time : 0.29 µs

Changes: 

Passed reference to ringbuffer instead of whole trade.
Instantly returned the order after getting filled.

Improvement: 1.08x


07/13/2026

# After Refactoring

Changes:

Created a Execution plan instead of executing in orderbook.

## Trial 1
----------------------------------------------------------
Benchmark                Time             CPU   Iterations
----------------------------------------------------------
BM_ProcessOrder    2230096 ns      2178801 ns        10913

Time: 2230 µs

Changes:

Performance has dropped significantly after refactoring codebase, now I am passing pointer of order instead of reference.


## Trial 2

----------------------------------------------------------
Benchmark                Time             CPU   Iterations
----------------------------------------------------------
BM_ProcessOrder    2451709 ns      2395216 ns        11532

Time: 2451.7 µs

Changes:

Performance has fallen even more, changed the pointers back to reference.

