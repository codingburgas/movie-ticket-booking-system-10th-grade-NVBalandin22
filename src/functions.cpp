#include "../include/functions.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>
#include <map>

void loadData(std::vector<Cinema>& cinemas, std::vector<Movie>& movies) {
    std::ifstream inFile("data/data.txt");
    if (!inFile) {
        Cinema cinema = {"CinemaCity", {
            {1, {
                {{"Inception", "Sci-Fi", "English", "2010-07-16"}, "18:00",
                    {{1,"silver",false},{2,"gold",false},{3,"platinum",false},{4,"silver",false},{5,"gold",false}}},
                {{"Interstellar", "Sci-Fi", "English", "2014-11-07"}, "21:00",
                    {{1,"silver",false},{2,"gold",false},{3,"platinum",false},{4,"silver",false},{5,"gold",false}}}
            }},
            {2, {
                {{"Dune", "Sci-Fi", "English", "2021-10-22"}, "20:00",
                    {{1,"silver",false},{2,"gold",false},{3,"platinum",false},{4,"silver",false},{5,"gold",false}}}
            }}
        }};
        cinemas.push_back(cinema);
        for (const Hall& h : cinema.halls)
            for (const Show& s : h.shows)
                movies.push_back(s.movie);
        return;
    }

    cinemas.clear();
    movies.clear();

    std::string line;
    Cinema cinema;
    Hall hall;

    while (getline(inFile, line)) {
        std::istringstream iss(line);
        std::string keyword;
        iss >> keyword;

        if (keyword == "Cinema") {
            if (!cinema.name.empty()) {
                if (!hall.shows.empty()) {
                    cinema.halls.push_back(hall);
                    hall.shows.clear();
                }
                cinemas.push_back(cinema);
                cinema.halls.clear();
            }
            iss >> cinema.name;
        } else if (keyword == "Hall") {
            if (!hall.shows.empty()) {
                cinema.halls.push_back(hall);
                hall.shows.clear();
            }
            iss >> hall.hallNumber;
        } else if (keyword == "Show") {
            Show show;
            iss >> show.movie.title >> show.movie.genre >> show.movie.language >> show.movie.releaseDate >> show.time;

            std::string seatData;
            while (iss >> seatData) {
                std::istringstream seatStream(seatData);
                std::string number, type, booked;
                getline(seatStream, number, ':');
                getline(seatStream, type, ':');
                getline(seatStream, booked, ':');

                Seat seat;
                seat.number = std::stoi(number);
                seat.type = type;
                seat.booked = (booked == "1");
                show.seats.push_back(seat);
            }
            hall.shows.push_back(show);
            movies.push_back(show.movie);
        }
    }

    if (!hall.shows.empty()) {
        cinema.halls.push_back(hall);
    }
    if (!cinema.name.empty()) {
        cinemas.push_back(cinema);
    }
}

void saveData(const std::vector<Cinema>& cinemas) {
    std::ofstream outFile("data/data.txt");
    for (const Cinema& c : cinemas) {
        outFile << "Cinema " << c.name << "\n";
        for (const Hall& h : c.halls) {
            outFile << "Hall " << h.hallNumber << "\n";
            for (const Show& s : h.shows) {
                outFile << "Show " << s.movie.title << " " << s.movie.genre << " "
                        << s.movie.language << " " << s.movie.releaseDate << " " << s.time;
                for (const Seat& seat : s.seats) {
                    outFile << " " << seat.number << ":" << seat.type << ":" << (seat.booked ? 1 : 0);
                }
                outFile << "\n";
            }
        }
    }
}

void searchMovie(const std::vector<Movie>& movies) {
    std::string search;
    std::cout << "Enter title, genre, language, or release date: ";std::getline(std::cin, search);
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
    int hallNumber, seatNumber, userType;
    double totalCost = 0.0;

    std::map<std::string, double> seatPrices = {
        {"silver", 10.0}, {"gold", 15.0}, {"platinum", 20.0}
    };

    std::cout << "Enter cinema name: ";std::getline(std::cin, cinemaName);

    Cinema* cinema = nullptr;
    for (Cinema& c : cinemas)
        if (c.name == cinemaName) cinema = &c;

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
    for (Hall& h : cinema->halls)
        if (h.hallNumber == hallNumber) hall = &h;

    if (!hall) {
        std::cout << "Hall not found.\n";
        return;
    }

    Show* selectedShow = nullptr;
    for (Show& show : hall->shows)
        if (show.movie.title == movieTitle) selectedShow = &show;

    if (!selectedShow) {
        std::cout << "Show not found.\n";
        return;
    }

    int seatsPerRow = 5;
    std::cout << "Available seats:\n";
    for (size_t i = 0; i < selectedShow->seats.size(); ++i) {
        const Seat& seat = selectedShow->seats[i];
        std::string typeShort = seat.type.substr(0,1);
        std::string display = seat.booked ? "X" : typeShort;

        std::cout << "[" << seat.number << ":" << display << "] ";

        if ((i+1) % seatsPerRow == 0)
            std::cout << "\n";
    }
    std::cout << "\nLegend: S = Silver, G = Gold, P = Platinum, X = Booked\n";

    int seatCount;
    std::cout << "\nHow many seats?: ";
    std::cin >> seatCount;

    std::vector<int> seatsToBook;
    std::cout << "Enter seat numbers:\n";
    for (int i = 0; i < seatCount; ++i) {
        std::cin >> seatNumber;
        bool seatFound = false;

        for (Seat& seat : selectedShow->seats) {
            if (seat.number == seatNumber && !seat.booked) {
                seat.booked = true;
                totalCost += seatPrices[seat.type];
                seatFound = true;
                seatsToBook.push_back(seatNumber);
                break;
            }
        }

        if (!seatFound) {
            std::cout << "Seat " << seatNumber << " unavailable. Booking cancelled.\n";
            for (int bookedNum : seatsToBook)
                for (Seat& s : selectedShow->seats)
                    if (s.number == bookedNum) s.booked = false;
            return;
        }
    }

    std::cout << "Total cost: $" << totalCost << "\n";

    std::cout << "1.Online\n2.Walk-in\nChoose: ";
    std::cin >> userType;

    if (userType == 1) {
        std::cout << "Paid online (credit).\n";
    } else if (userType == 2) {
        int paymentMethod;
        std::cout << "1.Cash 2.Credit\n";std::cin >> paymentMethod;
        std::cout << (paymentMethod == 1 ? "Paid cash.\n" : "Paid credit.\n");
    } else {
        std::cout << "Invalid payment. Cancelled.\n";
        for (int bookedNum : seatsToBook)
            for (Seat& s : selectedShow->seats)
                if (s.number == bookedNum) s.booked = false;
        return;
    }

    std::cout << "Seats booked!\n";
}

void addMovie(std::vector<Movie>& movies) {
    Movie m;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter title: ";std::getline(std::cin, m.title);
    std::cout << "Enter genre: ";std::getline(std::cin, m.genre);
    std::cout << "Enter language: ";std::getline(std::cin, m.language);
    std::cout << "Enter release date: ";std::getline(std::cin, m.releaseDate);
    movies.push_back(m);
    std::cout << "Movie added.\n";
}

void updateMovie(std::vector<Movie>& movies) {
    std::string title;
    std::cout << "Enter movie title to update: ";
    std::getline(std::cin, title);

    for (Movie& m : movies) {
        if (m.title == title) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "New title: "; std::getline(std::cin, m.title);
            std::cout << "New genre: "; std::getline(std::cin, m.genre);
            std::cout << "New language: "; std::getline(std::cin, m.language);
            std::cout << "New release date: "; std::getline(std::cin, m.releaseDate);
            std::cout << "Movie updated.\n";
            return;
        }
    }
    std::cout << "Movie not found.\n";
}

void removeMovie(std::vector<Movie>& movies) {
    std::string title;
    std::cout << "Enter title to remove: "; std::getline(std::cin, title);
    for (auto it = movies.begin(); it != movies.end(); ++it) {
        if (it->title == title) {
            movies.erase(it);
            std::cout << "Movie removed.\n";
            return;
        }
    }
    std::cout << "Movie not found.\n";
}

void addShow(std::vector<Cinema>& cinemas) {
    std::string cinemaName, movieTitle, time;
    int hallNumber;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Cinema name: "; std::getline(std::cin, cinemaName);
    Cinema* cinema = nullptr;
    for (Cinema& c : cinemas) if (c.name == cinemaName) cinema = &c;
    if (!cinema) { std::cout << "Cinema not found.\n"; return; }

    std::cout << "Hall number: "; std::cin >> hallNumber;
    Hall* hall = nullptr;
    for (Hall& h : cinema->halls) if (h.hallNumber == hallNumber) hall = &h;
    if (!hall) { std::cout << "Hall not found.\n"; return; }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    Show show;

    std::cout << "Movie title: "; std::getline(std::cin, show.movie.title);
    std::cout << "Genre: "; std::getline(std::cin, show.movie.genre);
    std::cout << "Language: "; std::getline(std::cin, show.movie.language);
    std::cout << "Release date: "; std::getline(std::cin, show.movie.releaseDate);
    std::cout << "Show time: "; std::getline(std::cin, show.time);

    show.seats = {{1,"silver",false},{2,"gold",false},{3,"platinum",false}};

    hall->shows.push_back(show);
    std::cout << "Show added successfully.\n";
}


void updateShow(std::vector<Cinema>& cinemas) {
    std::string cinemaName, movieTitle, time;
    int hallNumber;

    std::cout << "Cinema name: "; std::cin >> cinemaName;
    Cinema* cinema = nullptr;
    for (Cinema& c : cinemas) if (c.name == cinemaName) cinema = &c;
    if (!cinema) { std::cout << "Cinema not found.\n"; return; }

    std::cout << "Hall number: "; std::cin >> hallNumber;
    Hall* hall = nullptr;
    for (Hall& h : cinema->halls) if (h.hallNumber == hallNumber) hall = &h;
    if (!hall) { std::cout << "Hall not found.\n"; return; }

    std::cout << "Movie title: "; std::cin >> movieTitle;
    std::cout << "Show time: "; std::cin >> time;

    for (Show& s : hall->shows) {
        if (s.movie.title == movieTitle && s.time == time) {
            std::cout << "Movie title: "; std::getline(std::cin, s.movie.title);
            std::cout << "Genre: "; std::getline(std::cin, s.movie.genre);
            std::cout << "Language: "; std::getline(std::cin, s.movie.language);
            std::cout << "Release date: "; std::getline(std::cin, s.movie.releaseDate);
            std::cout << "Show time: "; std::getline(std::cin, s.time);
            std::cout << "Show updated.\n"; return;
        }
    }
    std::cout << "Show not found.\n";
}

void deleteShow(std::vector<Cinema>& cinemas) {
    std::string cinemaName, movieTitle, time;
    int hallNumber;

    std::cout << "Cinema name: "; std::getline(std::cin, cinemaName);
    Cinema* cinema = nullptr;
    for (Cinema& c : cinemas) if (c.name == cinemaName) cinema = &c;
    if (!cinema) { std::cout << "Cinema not found.\n"; return; }

    std::cout << "Hall number: "; std::cin >> hallNumber;
    Hall* hall = nullptr;
    for (Hall& h : cinema->halls) if (h.hallNumber == hallNumber) hall = &h;
    if (!hall) { std::cout << "Hall not found.\n"; return; }

    std::cout << "Movie title: "; std::getline(std::cin, movieTitle);
    std::cout << "Show time: "; std::getline(std::cin, time);

    for (auto it = hall->shows.begin(); it != hall->shows.end(); ++it) {
        if (it->movie.title == movieTitle && it->time == time) {
            hall->shows.erase(it);
            std::cout << "Show deleted.\n"; return;
        }
    }
    std::cout << "Show not found.\n";
}

void addCinema(std::vector<Cinema>& cinemas) {
    Cinema cinema;
    std::cout << "Enter new cinema name: ";std::getline(std::cin, cinema.name);
    cinemas.push_back(cinema);
    std::cout << "Cinema added.\n";
}

void updateCinema(std::vector<Cinema>& cinemas) {
    std::string name;
    std::cout << "Enter cinema name to update: "; std::getline(std::cin, name);

    for (Cinema& c : cinemas) {
        if (c.name == name) {
            std::cout << "New name: ";std::getline(std::cin, c.name);
            std::cout << "Cinema updated.\n";
            return;
        }
    }
    std::cout << "Cinema not found.\n";
}

void deleteCinema(std::vector<Cinema>& cinemas) {
    std::string name;
    std::cout << "Enter cinema name to delete: ";
    std::getline(std::cin, name);

    for (auto it = cinemas.begin(); it != cinemas.end(); ++it) {
        if (it->name == name) {
            cinemas.erase(it);
            std::cout << "Cinema deleted.\n";
            return;
        }
    }
    std::cout << "Cinema not found.\n";
}

void adminMenu(std::vector<Cinema>& cinemas, std::vector<Movie>& movies) {
    int choice;
    do {
        std::cout << "\nAdmin actions:\n";
        std::cout << "1. Add movie\n2. Delete movie\n3. Update movie\n";
        std::cout << "4. Add show\n5. Delete show\n6. Update show\n";
        std::cout << "7. Add cinema\n8. Delete cinema\n9. Update cinema\n";
        std::cout << "10. Exit\nChoice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: addMovie(movies); break;
            case 2: removeMovie(movies); break;
            case 3: updateMovie(movies); break;
            case 4: addShow(cinemas); break;
            case 5: deleteShow(cinemas); break;
            case 6: updateShow(cinemas); break;
            case 7: addCinema(cinemas); break;
            case 8: deleteCinema(cinemas); break;
            case 9: updateCinema(cinemas); break;
            case 10: std::cout << "Returning to main menu...\n"; break;
            default: std::cout << "Invalid choice.\n"; break;
        }

    } while (choice != 10);
}

void start() {
    std::vector<Cinema> cinemas;
    std::vector<Movie> movies;
    loadData(cinemas, movies);

    int userChoice;
    std::cout << "1.User 2.Admin\n";
    std::cin >> userChoice;

    if (userChoice == 2) {
        adminMenu(cinemas, movies);
    } else {
        int choice;
        while (true) {
            std::cout << "\n1.Search Movie 2.View Showtimes 3.Book Ticket 4.Exit\nChoice: ";
            std::cin >> choice;
            if (choice == 1) searchMovie(movies);
            else if (choice == 2) {
                std::string title;
                std::cout << "Movie title: "; std::cin >> title;
                for (Cinema& c : cinemas) c.displayShows(title);
            } else if (choice == 3) bookTicket(cinemas);
            else if (choice == 4) break;
            else std::cout << "Invalid.\n";
        }
    }
    saveData(cinemas);
}

