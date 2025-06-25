#ifndef SHOW_H
#define SHOW_H

#include "movie.h"
#include <string>
#include <vector>

struct Seat {
    int number;
    bool booked;
};

struct Show {
    Movie movie;
    std::string time;
    std::vector<Seat> seats;
};

#endif

