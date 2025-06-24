#include "../include/functions.h"
#include <iostream>

void addMovie(std::vector<Movie>& movies) {
    Movie m;
    std::cout << "Enter title: "; std::cin >> m.title;
    std::cout << "Enter genre: "; std::cin >> m.genre;
    std::cout << "Enter language: "; std::cin >> m.language;
    std::cout << "Enter release date: "; std::cin >> m.releaseDate;
    movies.push_back(m);
    std::cout << "Movie added.\n";
}

void removeMovie(std::vector<Movie>& movies) {
    std::string title;
    std::cout << "Enter title to remove: "; std::cin >> title;
    for (auto it = movies.begin(); it != movies.end(); ++it) {
        if (it->title == title) {
            movies.erase(it);
            std::cout << "Movie removed.\n";
            return;
        }
    }
    std::cout << "Movie not found.\n";
}

void searchMovie(const std::vector<Movie>& movies) {
    std::string search;
    std::cout << "Enter title, genre, language, or release date: ";
    std::cin >> search;
    for (const Movie& movie : movies) {
        if (movie.title == search || movie.genre == search ||
            movie.language == search || movie.releaseDate == search) {
            std::cout << "Found: " << movie.title << ", " << movie.genre
                      << ", " << movie.language << ", " << movie.releaseDate << "\n";
            }
    }
}


void start() {
    std::vector<Cinema> cinemas;
    std::vector<Movie> movies;

    Cinema cinema = {"Cinema City", {
            {1, { {{"Inception", "Sci-Fi", "English", "2010-07-16"}, "18:00"},
                  {{"Interstellar", "Sci-Fi", "English", "2014-11-07"}, "21:00"}}},
            {2, { {{"Dune", "Sci-Fi", "English", "2021-10-22"}, "20:00"}}}
    }};
    cinemas.push_back(cinema);
    for (const Hall& hall : cinema.halls) {
        for (const Show& show : hall.shows) {
            movies.push_back(show.movie);
        }
    }
    int choice;
    while (true) {
        std::cout << "\n1. Add Movie\n2. Remove Movie\n3. Search Movie\n4. View Showtimes\n5. Exit\nChoice: ";
        std::cin >> choice;
        if (choice == 1) {
            addMovie(movies);
        } else if (choice == 2) {
            removeMovie(movies);
        } else if (choice == 3) {
            searchMovie(movies);
        } else if (choice == 4) {
            std::string movieTitle;
            std::cout << "Enter movie title: ";
            std::cin >> movieTitle;
            for (Cinema& c : cinemas) {
                c.displayShows(movieTitle);
            }
        } else if (choice == 5) {
            break;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }
}