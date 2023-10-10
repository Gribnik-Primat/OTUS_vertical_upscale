#include "NormalState.h"
#include "ThreadExecutor.h"

NormalState::NormalState(ThreadExecutor& executor) : State(executor) {}

State* NormalState::handleSoftStop() {
    executor_.setStopRequested(true);
    return this;
}

State* NormalState::handleHardStop() {
    executor_.setStopRequested(true);
    return nullptr; // Indicates thread termination
}
