#pragma once

#include <functional>

class Command {
public:
    Command(std::function<void()> func) : func_(func) {}

    void execute() const {
        try {
            func_();
        } catch (...) {
            // Ignore exceptions
        }
    }

private:
    std::function<void()> func_;
};
