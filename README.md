# C++ Conductor

A high-performance, fixed-size thread pool library implemented from scratch in C++ to manage concurrent task execution. Utilizes low-level concurrency primitives (mutexes, condition variables) for thread safety and to prevent race conditions. Built with CMake and validated using Google Test (GTest) for correctness and performance.

## Features
- Fixed worker threads for efficient task queuing and execution.
- Future-based async results for enqueued tasks.
- Thread-safe operations with minimal overhead.
- Unit tests covering basic and concurrent scenarios.

## Tech Stack
- C++11 (core, with std threads/mutexes)
- CMake (build system)
- GTest (unit testing)

## Installation
1. Install CMake, GTest, and a C++ compiler (e.g., `brew install cmake googletest` on macOS).
2. Clone: `git clone https://github.com/martinchernyavskiy/cpp-conductor.git`
3. Build: `cmake . && make`

## Usage
Include `threadpool.h`:
```cpp
#include "threadpool.h"
int main() {
    ThreadPool pool(4);
    auto future = pool.enqueue([] { return 42; });
    std::cout << future.get() << std::endl; // 42
    return 0;
}