cmake_minimum_required(VERSION 3.29)
project(movie_ticket_booking_system_10th_grade_NVBalandin22)

set(CMAKE_CXX_STANDARD 20)

add_executable(movie_ticket_booking_system_10th_grade_NVBalandin22
        src/main.cpp
        src/functions.cpp
        include/functions.h
        include/movie.h
        include/show.h
        include/cinema.h
        src/cinema.cpp
        src/movie.cpp
        src/show.cpp
)
