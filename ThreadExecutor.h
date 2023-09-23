#pragma once

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Command.h"

class ThreadExecutor {
public:
    ThreadExecutor();

    void start();

    void stopHard();

    void stopSoft();

    void addCommand(const Command& command);

private:
    void workerThread();

    std::queue<Command> commandQueue_;
    std::vector<std::thread> threads_;
    bool stopRequested_ = false;
    bool stopWhenEmpty_ = false;
    bool executing_ = false;
    std::mutex mutex_;
    std::condition_variable cv_;
};
