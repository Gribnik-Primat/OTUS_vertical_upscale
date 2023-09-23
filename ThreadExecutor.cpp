#include "ThreadExecutor.h"
#include "State.h"
#include "NormalState.h"

ThreadExecutor::ThreadExecutor() : currentState_(new NormalState(*this)) {}

void ThreadExecutor::start() {
    threads_.emplace_back(&ThreadExecutor::workerThread, this);
}

void ThreadExecutor::stopHard() {
    currentState_ = currentState_->handleHardStop();
}

void ThreadExecutor::stopSoft() {
    currentState_ = currentState_->handleSoftStop();
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
            cv_.wait(lock, [this] { return stopRequested_ || !commandQueue_.empty(); });

            if (stopRequested_ && commandQueue_.empty()) {
                break;
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
