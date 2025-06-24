#include "../include/cinema.h"
#include <iostream>

void Cinema::displayShows(const std::string& movieTitle) {
    for (const Hall& hall : halls) {
        for (const Show& show : hall.shows) {
            if (show.movie.title == movieTitle) {
                std::cout << "Hall: " << hall.hallNumber << ", Time: " << show.time << "\n";
            }
        }
    }
}