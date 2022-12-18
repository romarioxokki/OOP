cmake_minimum_required(VERSION 3.21)
project(lab7)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab7 main.cpp Forum.h User.h Section.h Moderator.h Troll.h User.cpp Troll.cpp Moderator.cpp Section.cpp Forum.cpp)
