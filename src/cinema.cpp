#include "../include/cinema.h"
#include <iostream>

void Cinema::displayShows(const std::string& movieTitle) {
    for (const Hall& hall : halls) {
        for (const Show& show : hall.shows) {
            if (show.movie.title == movieTitle) {
                std::cout << name << "Hall: " << hall.hallNumber << ", Time: " << show.time << "\n";
            }
        }
    }
}

void Cinema::displayAllShows() const {
    for (const Hall& hall : halls) {
        for (const Show& show : hall.shows) {
            std::cout << "Cinema: " << name
                      << ", Hall: "  << hall.hallNumber
                      << ", Movie: " << show.movie.title
                      << ", Time: "  << show.time << '\n';
        }
    }
}