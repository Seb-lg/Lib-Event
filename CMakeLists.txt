cmake_minimum_required(VERSION 3.13)
project(Lib_Event)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(utils)

find_package (Threads)

add_executable(Lib_Event
        utils/TimedEvent.cpp
        utils/TimedEvent.hpp
        utils/TimedEventAdmin.cpp
        utils/TimedEventAdmin.hpp
        Event.cpp
        Event.hpp
        EventAdmin.cpp
        EventAdmin.hpp
        EventManager.cpp
        EventManager.hpp test/Main.cpp)

target_link_libraries (Lib_Event ${CMAKE_THREAD_LIBS_INIT})
