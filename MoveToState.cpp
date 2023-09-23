#include "ThreadExecutor.h" 
#include "NormalState.h"
#include "MoveToState.h"

MoveToState::MoveToState(ThreadExecutor& executor) : State(executor) {}

State* MoveToState::handleSoftStop() {
    executor_.setStopRequested(true);
    return this;
}

State* MoveToState::handleHardStop() {
    executor_.setStopRequested(true);
    return nullptr; // Indicates thread termination
}

State* MoveToState::handleMoveToCommand() {
    return new NormalState(executor_);
}
