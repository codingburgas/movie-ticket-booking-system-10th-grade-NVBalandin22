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

void bookTicket(std::vector<Cinema>& cinemas) {
    std::string cinemaName, movieTitle;
    int hallNumber, seatNumber;
    int paymentMethod, userType;

    std::cout << "Enter cinema name: ";
    std::cin >> cinemaName;

    Cinema* cinema = nullptr;
    for (Cinema& c : cinemas) {
        if (c.name == cinemaName) {
            cinema = &c;
            break;
        }
    }

    if (!cinema) {
        std::cout << "Cinema not found.\n";
        return;
    }

    std::cout << "Enter movie title: ";
    std::cin >> movieTitle;

    cinema->displayShows(movieTitle);

    std::cout << "Choose hall number: ";
    std::cin >> hallNumber;

    Hall* hall = nullptr;
    for (Hall& h : cinema->halls) {
        if (h.hallNumber == hallNumber) {
            hall = &h;
            break;
        }
    }

    if (!hall) {
        std::cout << "Hall not found.\n";
        return;
    }

    Show* selectedShow = nullptr;
    for (Show& show : hall->shows) {
        if (show.movie.title == movieTitle) {
            selectedShow = &show;
            break;
        }
    }

    if (!selectedShow) {
        std::cout << "Show not found.\n";
        return;
    }

    std::cout << "Available seats:\n";
    for (Seat& seat : selectedShow->seats) {
        if (!seat.booked) {
            std::cout << seat.number << " ";
        }
    }

    std::cout << "\nChoose seat number: ";
    std::cin >> seatNumber;

    for (Seat& seat : selectedShow->seats) {
        if (seat.number == seatNumber && !seat.booked) {
            std::cout << "1. Online\n2. Walk-in\nChoose type: ";
            std::cin >> userType;

            if (userType == 1) {
                std::cout << "Online payment (credit card only).\n";
            } else if (userType == 2) {
                std::cout << "Walk-in payment: 1. Cash 2. Credit Card\n";
                std::cin >> paymentMethod;
                if (paymentMethod == 1)
                    std::cout << "Paid by cash.\n";
                else
                    std::cout << "Paid by credit card.\n";
            } else {
                std::cout << "Invalid user type.\n";
                return;
            }

            seat.booked = true;
            std::cout << "Seat booked successfully.\n";
            return;
        }
    }

    std::cout << "Seat unavailable or already booked.\n";
}

void start() {
    std::vector<Cinema> cinemas;
    std::vector<Movie> movies;

    Cinema cinema = {"CinemaCity", {
        {1, {
            {{"Inception", "Sci-Fi", "English", "2010-07-16"}, "18:00", {{1,false},{2,false},{3,false}}},
            {{"Interstellar", "Sci-Fi", "English", "2014-11-07"}, "21:00", {{1,false},{2,false},{3,false}}}
        }},
        {2, {
            {{"Dune", "Sci-Fi", "English", "2021-10-22"}, "20:00", {{1,false},{2,false},{3,false}}}
        }}
    }};
    cinemas.push_back(cinema);

    for (const Hall& hall : cinema.halls) {
        for (const Show& show : hall.shows) {
            movies.push_back(show.movie);
        }
    }

    int choice;
    while (true) {
        std::cout << "\n1.Add Movie\n2.Remove Movie\n3.Search Movie\n4.View Showtimes\n5.Book Ticket\n6.Exit\nChoice: ";
        std::cin >> choice;
        if (choice == 1) {
            addMovie(movies);
        } else if (choice == 2) {
            removeMovie(movies);
        } else if (choice == 3) {
            searchMovie(movies);
        } else if (choice == 4) {
            std::string title;
            std::cout << "Enter movie title: ";
            std::cin >> title;
            for (Cinema& c : cinemas) {
                c.displayShows(title);
            }
        } else if (choice == 5) {
            bookTicket(cinemas);
        } else if (choice == 6) {
            break;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }
}
