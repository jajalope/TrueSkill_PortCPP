cmake_minimum_required(VERSION 3.21)
project(TrueSkill_PortCPP)

set(CMAKE_CXX_STANDARD 20)

add_executable(TrueSkill_PortCPP main.cpp Team.cpp Team.h Gaussian.cpp Gaussian.h)
