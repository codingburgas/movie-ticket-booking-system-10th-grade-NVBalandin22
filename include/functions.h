#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include "cinema.h"
#include "movie.h"

void start();
void addMovie(std::vector<Movie>& movies);
void removeMovie(std::vector<Movie>& movies);
void searchMovie(const std::vector<Movie>& movies);
void bookTicket(std::vector<Cinema>& cinemas);

#endif