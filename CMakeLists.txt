cmake_minimum_required(VERSION 3.25)
project(projeto2DA)

set(CMAKE_CXX_STANDARD 17)

add_executable(projeto2DA src/main.cpp src/utils/graph.h src/utils/graph.cpp src/utils/csv_reader.h src/utils/csv_reader.cpp src/manager.h src/manager.cpp src/heuristics.cpp)
