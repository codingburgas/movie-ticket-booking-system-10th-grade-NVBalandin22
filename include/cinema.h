#ifndef CINEMA_H
#define CINEMA_H

#include <string>
#include <vector>
#include "show.h"

struct Hall {
    int hallNumber;
    std::vector<Show> shows;
};

struct Cinema {
    std::string name;
    std::vector<Hall> halls;

    void displayShows(const std::string& movieTitle);
};

#endif