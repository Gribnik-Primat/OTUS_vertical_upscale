cmake_minimum_required(VERSION 3.10)
project(SpaceBattle)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
set(SOURCES
    Command.cpp
    Command.h
    ThreadExecutor.cpp
    ThreadExecutor.h
    State.h
    NormalState.h
    NormalState.cpp
    MoveToState.cpp
    MoveToState.h
)

# Add test files
set(TEST_SOURCES
    Tests.cpp
    gtest_main.cpp
)

# Include directories
include_directories(include)

# Find Google Test package
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Create executable for tests
add_executable(TankGame ${TEST_SOURCES} ${SOURCES})
target_link_libraries(TankGame ${GTEST_BOTH_LIBRARIES})
