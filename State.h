#pragma once

class ThreadExecutor; // Forward declaration

class State {
public:
    State(ThreadExecutor& executor) : executor_(executor) {}

    virtual State* handleSoftStop() { return this; }
    virtual State* handleHardStop() { return this; }
    virtual State* handleMoveToCommand() { return this; }

protected:
    ThreadExecutor& executor_;
};
