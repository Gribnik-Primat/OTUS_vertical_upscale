#pragma once

#include "State.h"

class NormalState : public State {
public:
    NormalState(ThreadExecutor& executor);

    State* handleSoftStop() override;
    State* handleHardStop() override;
};
