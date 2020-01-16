cmake_minimum_required(VERSION 3.15)
project(Socke)

set(CMAKE_CXX_STANDARD 14)
add_executable(Socke main.cpp Socket/Socket.cpp Socket/Socket.h domObjects/bed.h domObjects/bed.cpp domObjects/chair.h domObjects/chair.cpp domObjects/lamp.h domObjects/lamp.cpp domObjects/wall.h domObjects/wall.cpp domObjects/door.h domObjects/door.cpp domObjects/fridge.h domObjects/fridge.cpp domObjects/pillar.h domObjects/pillar.cpp includes.h domObjects/domObject.h domObjects/domObject.cpp Socket/webSocket.cpp Socket/webSocket.h timeKeeper.cpp timeKeeper.h)


