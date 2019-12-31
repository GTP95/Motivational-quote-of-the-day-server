cmake_minimum_required(VERSION 3.15)
project(Motivational_quote_of_the_day_server C)

set(CMAKE_C_STANDARD 11)
set(GCC_OPTIMIZATION_FLAGS "-O3 -march=native")

add_executable(Motivational_quote_of_the_day_server main.c)

target_link_libraries(Motivational_quote_of_the_day_server -lpthread)