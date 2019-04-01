cmake_minimum_required(VERSION 3.13)
project(AlgoLab_2_4)

set(CMAKE_CXX_STANDARD 14)

add_executable(AlgoLab_2_4 main.cpp)
add_executable(pathmgep pathmgep.cpp pathmgep.in pathmgep.out)
add_executable(pathbgep pathbgep.cpp pathbgep.in pathbgep.out)
add_executable(pathsg pathsg.cpp pathsg.in pathsg.out)
add_executable(negcycle negcycle.cpp negcycle.in negcycle.out)
add_executable(path path.cpp path.in path.out)
add_executable(kpath kpath.cpp)