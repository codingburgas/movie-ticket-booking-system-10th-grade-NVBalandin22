#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include "cinema.h"
#include "movie.h"

void start();

void addMovie(std::vector<Movie>& movies);
void updateMovie(std::vector<Movie>& movies);
void removeMovie(std::vector<Movie>& movies);

void searchMovie(const std::vector<Cinema>& cinemas);
void bookTicket(std::vector<Cinema>& cinemas);
void printTickets(const Cinema& cinema, const Hall& hall, const Show& show, const std::vector<int>& bookedSeats);

void loadData(std::vector<Cinema>& cinemas, std::vector<Movie>& movies);
void saveData(const std::vector<Cinema>& cinemas);
void adminMenu(std::vector<Cinema>& cinemas, std::vector<Movie>& movies);

void addShow(std::vector<Cinema>& cinemas);
void deleteShow(std::vector<Cinema>& cinemas);
void updateShow(std::vector<Cinema>& cinemas);

void addCinema(std::vector<Cinema>& cinemas);
void deleteCinema(std::vector<Cinema>& cinemas);
void updateCinema(std::vector<Cinema>& cinemas);

void addNotification(const std::string& notification);
void viewNotifications();
bool adminLogin();


#endif