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
1. Install dependencies:
   - macOS: `brew install cmake googletest`
   - Linux (Ubuntu): `sudo apt install cmake libgtest-dev`
   - Windows: Install CMake from cmake.org, GTest via vcpkg or build from source.
2. Clone: `git clone https://github.com/martinchernyavskiy/cpp-conductor.git`
3. Navigate: `cd cpp-conductor`
4. Build: `cmake . && make`
   - This generates the library (libthreadpool.a) and tests (conductor_tests).

**Note**: On Windows, use CMake GUI or `cmake -G "MinGW Makefiles" .` if using MinGW.

## Usage
The library is header-based with implementation in threadpool.cpp. Integrate it into your C++ project to run tasks concurrently (e.g., for parallel computations or I/O).

### Step 1: Include in Your Project
- Copy threadpool.h and threadpool.cpp to your source dir.
- In your code:
  ```cpp
  #include "threadpool.h"
  ```
- Build with your compiler, linking the library if separate (e.g., add to CMakeLists.txt: `target_link_libraries(your_app threadpool)`).

### Step 2: Basic Example (Single Task)
Create a main.cpp:
```cpp
#include "threadpool.h"
#include <iostream>

int main() {
    ThreadPool pool(4);  // 4 worker threads
    auto future = pool.enqueue([] { return 42; });  // Enqueue a lambda task
    std::cout << future.get() << std::endl;  // Wait and print result: 42
    return 0;
}
```
- Compile: `g++ main.cpp threadpool.cpp -std=c++11 -pthread -o example`
- Run: `./example`

### Step 3: Concurrent Example (Multiple Tasks)
For parallel work, like processing numbers:
```cpp
#include "threadpool.h"
#include <iostream>
#include <vector>

int main() {
    ThreadPool pool(2);  // 2 threads
    std::vector<std::future<int>> results;
    for (int i = 0; i < 10; ++i) {
        results.emplace_back(pool.enqueue([i] { return i * 2; }));  // Enqueue 10 tasks
    }
    for (auto& res : results) {
        std::cout << res.get() << " ";  // Outputs: 0 2 4 ... 18
    }
    std::cout << std::endl;
    return 0;
}
```
- The threads share the work, finishing faster than sequential code.
- Compile/Run as above.

### Troubleshooting
- **Build Errors**: Ensure C++11+ (`-std=c++11`), pthread for threads (`-pthread` on Linux/macOS).
- **GTest Not Found**: Check install path; add `-DGTEST_ROOT=/path/to/gtest` to cmake if needed.
- **Runtime Issues**: If deadlocks, check task logic (e.g., no infinite loops).
- **Windows**: Use Visual Studio for easier integration; add pthread shim if needed.

## Testing
After build, run `./conductor_tests`. It includes:
- Basic: Single task execution.
- Concurrent: Multiple tasks with results verification.

## License
MIT License—free to use and modify.
