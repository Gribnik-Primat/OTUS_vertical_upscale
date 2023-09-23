#pragma once

#include "State.h"

class MoveToState : public State {
public:
    MoveToState(ThreadExecutor& executor);

    State* handleSoftStop() override;
    State* handleHardStop() override;
    State* handleMoveToCommand() override;
};
