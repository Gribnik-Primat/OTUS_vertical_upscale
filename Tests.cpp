#include <gtest/gtest.h>
#include <thread>
#include "ThreadExecutor.h"

TEST(ThreadExecutorTest, SoftStop) {
    ThreadExecutor executor;

    executor.start();

    // Adding commands to the queue
    executor.addCommand(Command([] { std::this_thread::sleep_for(std::chrono::seconds(1)); }));
    executor.addCommand(Command([] { std::this_thread::sleep_for(std::chrono::seconds(1)); }));
    executor.addCommand(Command([] { std::this_thread::sleep_for(std::chrono::seconds(1)); }));

    // Stopping the executor (soft stop)
    executor.stopSoft();
}

TEST(ThreadExecutorTest, HardStop) {
    ThreadExecutor executor;

    executor.start();

    // Adding commands to the queue
    executor.addCommand(Command([] { std::this_thread::sleep_for(std::chrono::seconds(1)); }));
    executor.addCommand(Command([] { std::this_thread::sleep_for(std::chrono::seconds(1)); }));
    executor.addCommand(Command([] { std::this_thread::sleep_for(std::chrono::seconds(1)); }));

    // Stopping the executor (hard stop)
    executor.stopHard();
}
