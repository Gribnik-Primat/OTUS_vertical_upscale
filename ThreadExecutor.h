#pragma once

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <optional>
#include "Command.h"

class State; // Forward declaration

class ThreadExecutor {
public:
    ThreadExecutor();

    void start();

    void stopHard();

    void stopSoft();

    void addCommand(const Command& command);

    void setStopRequested(bool stopRequested);

    bool isStopRequested() const;

    State* getCurrentState() const; 

private:
    void workerThread();

    std::queue<Command> commandQueue_;
    std::vector<std::thread> threads_;
    bool stopRequested_ = false;
    bool stopWhenEmpty_ = false;
    bool executing_ = false;
    std::mutex mutex_;
    std::condition_variable cv_;
    State* currentState_; 

    friend class State;
};
