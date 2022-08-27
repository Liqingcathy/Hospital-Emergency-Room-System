cmake_minimum_required(VERSION 3.17)
project(Patient System)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -W -Wall -Werror -pedantic")

add_executable(HW8 Main.cpp Patient.h PatientPriorityQueue.h)