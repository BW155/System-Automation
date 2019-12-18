cmake_minimum_required(VERSION 3.15)
project(System_Automation)

set(CMAKE_CXX_STANDARD 14)

include_directories(raspberry-pi)
include_directories(raspberry-pi/domObjects)
include_directories(raspberry-pi/json)
include_directories(raspberry-pi/Socket)

add_executable(System_Automation
        cmake-build-debug/cmake_install.cmake
        cmake-build-debug/CMakeCache.txt
        cmake-build-debug/Makefile
        cmake-build-debug/System_Automation.cbp
        front-end/README.md
        raspberry-pi/domObjects/bed.cpp
        raspberry-pi/domObjects/bed.h
        raspberry-pi/domObjects/chair.cpp
        raspberry-pi/domObjects/chair.h
        raspberry-pi/domObjects/domObject.cpp
        raspberry-pi/domObjects/domObject.h
        raspberry-pi/domObjects/door.cpp
        raspberry-pi/domObjects/door.h
        raspberry-pi/domObjects/fridge.cpp
        raspberry-pi/domObjects/fridge.h
        raspberry-pi/domObjects/lamp.cpp
        raspberry-pi/domObjects/lamp.h
        raspberry-pi/domObjects/main
        raspberry-pi/domObjects/pillar.cpp
        raspberry-pi/domObjects/pillar.h
        raspberry-pi/domObjects/wall.cpp
        raspberry-pi/domObjects/wall.h
        raspberry-pi/json/json.hpp
        raspberry-pi/Socket/Socket.cpp
        raspberry-pi/Socket/Socket.h
        raspberry-pi/Socket/webSocket.cpp
        raspberry-pi/Socket/webSocket.h
        raspberry-pi/CMakeLists.txt
        raspberry-pi/includes.h
        raspberry-pi/includes.h.gch
        raspberry-pi/main
        raspberry-pi/main.cpp
        raspberry-pi/README.md
        raspberry-pi/timeKeeper
        raspberry-pi/timeKeeper.cpp
        raspberry-pi/timeKeeper.h
        raspberry-pi/timeKeeper.h.gch
        CMakeLists.txt
        CommunicatiePlan
        README.md)
