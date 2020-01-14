cmake_minimum_required(VERSION 2.8.12.2)
project(Motivational_quote_of_the_day_server C)

set(CMAKE_C_STANDARD 11)
#https://stackoverflow.com/questions/11783932/how-do-i-add-a-linker-or-compile-flag-in-a-cmake-file
set(GCC_WARINING_FLAGS "-Wall -Wextra")
set(GCC_OPTIMIZATION_FLAGS "-O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_OPTIMIZATION_FLAGS}")

add_executable(mqotd main.c)

target_link_libraries(mqotd -lpthread)

install(CODE "execute_process(COMMAND ./install.sh)")
