cmake_minimum_required(VERSION 3.13)
project(AlgoLab_2_5)

set(CMAKE_CXX_STANDARD 14)
set(numb 10)
add_executable(AlgoLab_2_5 main.cpp)
add_executable(MaxFlow maxflow.cpp)
add_executable(Matching matching.cpp)
add_executable(Matching2 matching2.cpp)
add_executable(Decopmposition decomposition.cpp)
add_executable(Circulation circulation.cpp)
message("Hello " ${numb})
unset(numb)
