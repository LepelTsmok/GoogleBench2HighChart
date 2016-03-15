cmake_minimum_required(VERSION 3.0)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
   message(FATAL_ERROR "You don't want to configure in the source directory!")
endif()

project(GoogleBench2HighChart)

find_package(Qt5 REQUIRED COMPONENTS Core)
add_executable(GoogleBench2HighChart Commandline.cpp HTMLOutput.cpp JSONConvert.cpp main.cpp)
target_include_directories(GoogleBench2HighChart PRIVATE "${Qt5Core_INCLUDE_DIRS}")
target_compile_options(GoogleBench2HighChart PRIVATE "-std=c++11;${Qt5Core_EXECUTABLE_COMPILE_FLAGS}")
target_link_libraries(GoogleBench2HighChart ${Qt5Core_LIBRARIES})
