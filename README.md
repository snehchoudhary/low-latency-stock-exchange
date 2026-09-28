# Low-Latency Stock Exchange & Matching Engine

A high-performance stock exchange and limit order book matching engine written in **C++20**. It matches buy and sell orders using **price-time priority** with FIFO ordering, and is designed around low-latency principles such as custom memory management and cache-friendly data structures.

> **Status: Work in progress.** Core matching functionality is in place, and performance work is ongoing. See the [Roadmap](#roadmap).

## Features

- **Limit order book** with separate bid and ask sides
- **Price-time priority matching:** best price first, then FIFO within each price level
- **Order lifecycle management:** place, cancel, and modify orders
- **Market data:** bid/ask management and spread calculation
- **Symbol-based order routing** to per-symbol order books
- **Integer-based price representation** to avoid floating-point rounding errors

## Performance Design

| Technique | Purpose |
|---|---|
| Custom memory pools | Avoid general-purpose heap allocation on the hot path |
| Zero-allocation techniques | Keep latency predictable while matching |
| `std::pmr` memory resources | Control allocation strategy for containers |
| SPSC queues | Lock-free hand-off between producer and consumer threads |
| Cache-aware data structures | Improve locality and reduce cache misses |
| Memory alignment | Avoid false sharing and unaligned access |
| Trivially copyable types | Cheap copies and safe use in queues and pools |

## Tech Stack

C++20 · STL · `std::pmr` · CMake · Ninja

## How Matching Works

1. An incoming order is routed to the order book for its symbol.
2. The engine compares it against the best price on the opposite side.
3. If prices cross, orders match in **price-time priority**: the best price first, then the oldest order at that price.
4. Any unfilled quantity of a limit order rests in the book at its price level.
5. Cancel and modify requests locate the resting order and update or remove it.

## Project Structure

```text
.
├── include/        # headers (order, order book, memory pool, queues)
├── src/            # implementation
├── tests/          # tests
├── benchmarks/     # benchmark code
├── CMakeLists.txt
└── README.md
```

*Change this tree to match your actual repository.*

## Getting Started

**Prerequisites:** a C++20 compiler (GCC 11+, Clang 13+, or MSVC 2019+), CMake 3.20+, and Ninja.

```bash
git clone https://github.com/snehchoudhary/YOUR-REPO.git
cd YOUR-REPO

cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

Run the executable:

```bash
./build/YOUR_EXECUTABLE_NAME
```

## Example

```text
Add order: BUY  100 @ 150.25
Add order: SELL  60 @ 150.25   -> Trade: 60 @ 150.25
Remaining: BUY  40 @ 150.25 (resting in book)
```

*Replace this with real output from your program.*

## Benchmarks

*Add your measured results here, for example orders per second or average matching latency, along with the machine and compiler used. Leave this section out until you have real numbers.*

## Roadmap

- [x] Limit order book with price-time priority matching
- [x] Order placement, cancellation, and modification
- [x] Symbol-based order routing
- [ ] Custom memory pools and `std::pmr` integration
- [ ] SPSC queue-based order pipeline
- [ ] Benchmark suite and latency measurements
- [ ] Unit tests for matching edge cases
- [ ] Market orders and additional order types

## Author

**Sneha Choudhary** · [GitHub](https://github.com/snehchoudhary) · [LinkedIn](https://www.linkedin.com/in/sneha-choudhary-58a5552a8/)
