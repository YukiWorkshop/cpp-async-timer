cmake_minimum_required(VERSION 3.2)
project(cpp-async-timer)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(cpp_async_timer_test AsyncTimer.hpp Test.cpp)
target_link_libraries(cpp_async_timer_test boost_system pthread)