#include <iostream>
#include "ThreadExecutor.h"

void printMessage(const std::string& message) {
    std::cout << "Thread ID: " << std::this_thread::get_id() << ", Message: " << message << std::endl;
}

int main() {
    ThreadExecutor executor;

    executor.start();

    // Adding commands to the queue
    executor.addCommand(Command([] { printMessage("Command 1"); }));
    executor.addCommand(Command([] { printMessage("Command 2"); }));
    executor.addCommand(Command([] { printMessage("Command 3"); }));

    // Stopping the executor (hard stop)
    executor.stopHard();

    return 0;
}
