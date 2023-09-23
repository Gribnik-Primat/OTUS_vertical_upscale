#include <gtest/gtest.h>
#include <thread>
#include "NormalState.h"
#include "MoveToState.h"
#include "ThreadExecutor.h"

TEST(ThreadExecutorTest, SoftStop) {
    ThreadExecutor executor;

    executor.start();

    // Adding commands to the queue
    executor.addCommand(Command([] { std::this_thread::sleep_for(std::chrono::seconds(1)); }));
    executor.addCommand(Command([] { std::this_thread::sleep_for(std::chrono::seconds(1)); }));
    executor.addCommand(Command([] { std::this_thread::sleep_for(std::chrono::seconds(1)); }));

    // Stopping the executor (soft stop)
    executor.stopSoft();
}

TEST(ThreadExecutorTest, HardStop) {
    ThreadExecutor executor;

    executor.start();

    // Adding commands to the queue
    executor.addCommand(Command([] { std::this_thread::sleep_for(std::chrono::seconds(1)); }));
    executor.addCommand(Command([] { std::this_thread::sleep_for(std::chrono::seconds(1)); }));
    executor.addCommand(Command([] { std::this_thread::sleep_for(std::chrono::seconds(1)); }));

    // Stopping the executor (hard stop)
    executor.stopHard();
}

TEST(NormalStateTest, HandleSoftStop) {
    ThreadExecutor executor;
    NormalState state(executor);

    State* nextState = state.handleSoftStop();

    EXPECT_TRUE(executor.isStopRequested());
    EXPECT_EQ(nextState, &state); 
}

TEST(NormalStateTest, HandleHardStop) {
    ThreadExecutor executor;
    NormalState state(executor);

    State* nextState = state.handleHardStop();

    EXPECT_TRUE(executor.isStopRequested());
    EXPECT_EQ(nextState, nullptr);
}

TEST(MoveToStateTest, HandleSoftStop) {
    ThreadExecutor executor;
    MoveToState state(executor);

    State* nextState = state.handleSoftStop();

    EXPECT_TRUE(executor.isStopRequested()); 
    EXPECT_EQ(nextState, &state); 
}

TEST(MoveToStateTest, HandleHardStop) {
    ThreadExecutor executor;
    MoveToState state(executor);

    State* nextState = state.handleHardStop();

    EXPECT_TRUE(executor.isStopRequested());
    EXPECT_EQ(nextState, nullptr); 
}

TEST(MoveToStateTest, HandleMoveToCommand) {
    ThreadExecutor executor;
    MoveToState state(executor);

    State* nextState = state.handleMoveToCommand();
    State* currentState = executor.getCurrentState(); // Store the current state

    EXPECT_EQ(nextState, dynamic_cast<NormalState*>(currentState));
}

