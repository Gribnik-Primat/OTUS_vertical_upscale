#include "ThreadExecutor.h"
#include "State.h"
#include "NormalState.h"

ThreadExecutor::ThreadExecutor() : currentState_(new NormalState(*this)) {}

void ThreadExecutor::start() {
    threads_.emplace_back(&ThreadExecutor::workerThread, this);
}

void ThreadExecutor::stopHard() {
    currentState_ = currentState_->handleHardStop();
    {
        std::unique_lock<std::mutex> lock(mutex_);
        stopRequested_ = true;
    }
    cv_.notify_all();

    for (std::thread& thread : threads_) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    threads_.clear();
}

void ThreadExecutor::stopSoft() {
    currentState_ = currentState_->handleSoftStop();
    {
        std::unique_lock<std::mutex> lock(mutex_);
        stopWhenEmpty_ = true;
        // If no commands are executing, stop immediately
        if (!executing_) {
            stopRequested_ = true;
        }
    }
    cv_.notify_all();

    for (std::thread& thread : threads_) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    threads_.clear();
}

void ThreadExecutor::addCommand(const Command& command) {
    std::unique_lock<std::mutex> lock(mutex_);
    commandQueue_.push(command);
    cv_.notify_one();
}

void ThreadExecutor::setStopRequested(bool stopRequested) {
    stopRequested_ = stopRequested;
}

bool ThreadExecutor::isStopRequested() const {
    return stopRequested_;
}

State* ThreadExecutor::getCurrentState() const {
    return currentState_;
}

void ThreadExecutor::workerThread() {
    while (true) {
        std::optional<Command> command;
        {
            std::unique_lock<std::mutex> lock(mutex_);
            cv_.wait(lock, [this] { return stopRequested_ || (!commandQueue_.empty() && stopWhenEmpty_); });

            if (stopRequested_ || (stopWhenEmpty_ && commandQueue_.empty())) {
                return;
            }

            if (!commandQueue_.empty()) {
                command = std::move(commandQueue_.front());
                commandQueue_.pop();
                executing_ = true;
            }
        }

        if (command) {
            command.value().execute();
            executing_ = false;
        }
    }
}
