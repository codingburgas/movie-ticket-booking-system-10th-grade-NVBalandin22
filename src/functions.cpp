#include "../include/functions.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>

void addMovie(std::vector<Movie>& movies) {
    Movie m;
    std::cout << "Enter title: "; std::cin >> m.title;
    std::cout << "Enter genre: "; std::cin >> m.genre;
    std::cout << "Enter language: "; std::cin >> m.language;
    std::cout << "Enter release date: "; std::cin >> m.releaseDate;
    movies.push_back(m);
    std::cout << "Movie added." << std::endl;
}

void removeMovie(std::vector<Movie>& movies) {
    std::string title;
    std::cout << "Enter title to remove: "; std::cin >> title;
    for (auto it = movies.begin(); it != movies.end(); ++it) {
        if (it->title == title) {
            movies.erase(it);
            std::cout << "Movie removed." << std::endl;
            return;
        }
    }
    std::cout << "Movie not found." << std::endl;
}

void searchMovie(const std::vector<Movie>& movies) {
    std::string search;
    std::cout << "Enter title, genre, language, or release date: ";
    std::cin >> search;
    for (const Movie& movie : movies) {
        if (movie.title == search || movie.genre == search ||
            movie.language == search || movie.releaseDate == search) {
            std::cout << "Found: " << movie.title << ", " << movie.genre
                      << ", " << movie.language << ", " << movie.releaseDate << std::endl;
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
        std::cout << "Cinema not found." << std::endl;
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
        std::cout << "Hall not found." << std::endl;
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
        std::cout << "Show not found." << std::endl;
        return;
    }

    std::cout << "Available seats:" << std::endl;
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
                std::cout << "Online payment (credit card only)." << std::endl;
            } else if (userType == 2) {
                std::cout << "Walk-in payment: 1. Cash 2. Credit Card" << std::endl;
                std::cin >> paymentMethod;
                if (paymentMethod == 1)
                    std::cout << "Paid by cash." << std::endl;
                else
                    std::cout << "Paid by credit card." << std::endl;
            } else {
                std::cout << "Invalid user type." << std::endl;
                return;
            }

            seat.booked = true;
            std::cout << "Seat booked successfully." << std::endl;
            return;
        }
    }

    std::cout << "Seat unavailable or already booked." << std::endl;
}

void loadData(std::vector<Cinema>& cinemas, std::vector<Movie>& movies) {
    std::ifstream inFile("data/data.txt");
    if (!inFile) {
        std::cout << "No saved data found. Initializing default cinema..." << std::endl;

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
        for (const Hall& h : cinema.halls)
            for (const Show& s : h.shows)
                movies.push_back(s.movie);
        return;
    }

    std::string line;
    Cinema cinema;
    Hall hall;
    while (getline(inFile, line)) {
        std::istringstream iss(line);
        std::string keyword;
        iss >> keyword;

        if (keyword == "Cinema") {
            if (!cinema.name.empty()) cinemas.push_back(cinema);
            cinema = Cinema{};
            iss >> cinema.name;
        }
        else if (keyword == "Hall") {
            if (!hall.shows.empty()) cinema.halls.push_back(hall);
            hall = Hall{};
            iss >> hall.hallNumber;
        }
        else if (keyword == "Show") {
            Show show;
            iss >> show.movie.title >> show.movie.genre >> show.movie.language >> show.movie.releaseDate >> show.time;
            int status;
            while (iss >> status) {
                show.seats.push_back({static_cast<int>(show.seats.size()) + 1, status == 1});
            }
            hall.shows.push_back(show);
            movies.push_back(show.movie);
        }
    }

    if (!hall.shows.empty()) cinema.halls.push_back(hall);
    if (!cinema.name.empty()) cinemas.push_back(cinema);

    inFile.close();
}

void saveData(const std::vector<Cinema>& cinemas) {
    std::ofstream outFile("data/data.txt");
    for (const Cinema& c : cinemas) {
        outFile << "Cinema " << c.name << std::endl;
        for (const Hall& h : c.halls) {
            outFile << "Hall " << h.hallNumber << std::endl;
            for (const Show& s : h.shows) {
                outFile << "Show " << s.movie.title << " " << s.movie.genre << " "
                        << s.movie.language << " " << s.movie.releaseDate << " " << s.time;
                for (const Seat& seat : s.seats) {
                    outFile << " " << (seat.booked ? 1 : 0);
                }
                outFile << std::endl;
            }
        }
    }
    outFile.close();
}

void start() {
    std::vector<Cinema> cinemas;
    std::vector<Movie> movies;

    loadData(cinemas, movies);

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
            std::cout << "Do you want to save changes?" << std::endl;
            std::string choice2;
            std::cin >> choice2;
            for (char &c : choice2) {
                c = static_cast<char>(std::tolower(c));
            }
            if(choice2 == "yes" || choice2 == "y") {
                saveData(cinemas);
                std::cout << "Data saved." << std::endl;
            }
            break;
        } else {
            std::cout << "Invalid choice." << std::endl;
        }
    }
}
