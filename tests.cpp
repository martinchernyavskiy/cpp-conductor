#include <gtest/gtest.h>
#include "threadpool.h"

TEST(ThreadPoolTest, BasicExecution) {
    ThreadPool pool(4);
    auto future = pool.enqueue([] { return 42; });
    EXPECT_EQ(future.get(), 42);
}

TEST(ThreadPoolTest, ConcurrentTasks) {
    ThreadPool pool(2);
    std::vector<std::future<int>> results;
    for (int i = 0; i < 10; ++i) {
        results.emplace_back(pool.enqueue([i] { return i * 2; }));
    }
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(results[i].get(), i * 2);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}