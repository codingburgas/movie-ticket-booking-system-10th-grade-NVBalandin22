#include "../include/functions.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <map>

Movie newMovie() {
    Movie m;
    std::cout << "Enter title: ";          std::getline(std::cin, m.title);
    std::cout << "Enter genre: ";          std::getline(std::cin, m.genre);
    std::cout << "Enter language: ";       std::getline(std::cin, m.language);
    std::cout << "Enter release date: ";   std::getline(std::cin, m.releaseDate);
    return m;
}

void loadData(std::vector<Cinema>& cinemas, std::vector<Movie>& movies) {
    std::ifstream in("data/data.txt");
    if (!in) {
        Cinema c{"CinemaCity",
                 {{1, {{{"Inception","Sci-Fi","English","2010-07-16"},"18:00",
                        {{1,"silver",false},{2,"gold",false},{3,"platinum",false}}}}}}};
        cinemas = {c};
        movies  = {c.halls[0].shows[0].movie};
        return;
    }

    cinemas.clear(); movies.clear();
    std::string line; Cinema cinema; Hall hall;

    while (std::getline(in, line)) {
        if (line.rfind("Cinema ", 0) == 0) {
            if (!cinema.name.empty()) {
                if (!hall.shows.empty()) { cinema.halls.push_back(hall); hall = {}; }
                cinemas.push_back(cinema);
                cinema = {};
            }
            cinema.name = line.substr(7);
        }
        else if (line.rfind("Hall ", 0) == 0) {
            if (!hall.shows.empty()) { cinema.halls.push_back(hall); hall = {}; }
            hall.hallNumber = std::stoi(line.substr(5));
        }
        else if (line.rfind("Show|", 0) == 0) {
            Show sh;
            std::string rest = line.substr(5);            // без "Show|"
            std::istringstream parts(rest);
            std::getline(parts, sh.movie.title,      '|');
            std::getline(parts, sh.movie.genre,      '|');
            std::getline(parts, sh.movie.language,   '|');
            std::getline(parts, sh.movie.releaseDate,'|');
            std::getline(parts, sh.time,             '|');

            std::string seatTok;
            while (std::getline(parts, seatTok, '|')) {
                if (seatTok.empty()) continue;
                size_t p1 = seatTok.find(':');
                size_t p2 = seatTok.rfind(':');
                if (p1 == std::string::npos || p2 == p1) continue;
                Seat seat{
                    std::stoi(seatTok.substr(0, p1)),
                    seatTok.substr(p1 + 1, p2 - p1 - 1),
                    seatTok.substr(p2 + 1) == "1"
                };
                sh.seats.push_back(seat);
            }
            hall.shows.push_back(sh);
            movies.push_back(sh.movie);
        }
    }
    if (!hall.shows.empty())   cinema.halls.push_back(hall);
    if (!cinema.name.empty())  cinemas.push_back(cinema);
}

void saveData(const std::vector<Cinema>& cinemas) {
    std::ofstream out("data/data.txt");
    for (const Cinema& c : cinemas) {
        out << "Cinema " << c.name << '\n';
        for (const Hall& h : c.halls) {
            out << "Hall " << h.hallNumber << '\n';
            for (const Show& s : h.shows) {
                out << "Show|"
                    << s.movie.title      << '|'
                    << s.movie.genre      << '|'
                    << s.movie.language   << '|'
                    << s.movie.releaseDate<< '|'
                    << s.time;
                for (const Seat& seat : s.seats)
                    out << '|' << seat.number << ':' << seat.type << ':' << (seat.booked ? 1 : 0);
                out << '\n';
            }
        }
    }
}


void addMovie(std::vector<Movie>& movies){
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    movies.push_back(newMovie());
    std::cout << "Movie added.\n";
}

void updateMovie(std::vector<Movie>& movies){
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string title; std::cout << "Title to update: "; std::getline(std::cin, title);
    for (Movie& m : movies) if (m.title == title) { m = newMovie(); std::cout << "Updated.\n"; return; }
    std::cout << "Movie not found.\n";
}

void removeMovie(std::vector<Movie>& movies){
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string title; std::cout << "Title to delete: "; std::getline(std::cin, title);
    for (auto it = movies.begin(); it != movies.end(); ++it) if (it->title == title) { movies.erase(it); std::cout << "Deleted.\n"; return; }
    std::cout << "Movie not found.\n";
}

void searchMovie(const std::vector<Cinema>& cinemas) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string q;
    std::cout << "Search by title / genre / language / date: ";
    std::getline(std::cin, q);

    bool any = false;
    for (const Cinema& c : cinemas)
        for (const Hall& h : c.halls)
            for (const Show& s : h.shows)
                if (s.movie.title       == q ||
                    s.movie.genre       == q ||
                    s.movie.language    == q ||
                    s.movie.releaseDate == q)
                {
                    any = true;
                    std::cout << "Cinema: " << c.name << ", Hall: " << h.hallNumber << ", Time: " << s.time << "  ->  Title:" << s.movie.title << " (genre" << s.movie.genre << ", language: "<< s.movie.language << ", release date: " << s.movie.releaseDate << ")\n";
                }

    if (!any) std::cout << "Nothing found.\n";
}


void addCinema(std::vector<Cinema>& cinemas) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    Cinema c;
    std::cout << "Cinema name: ";std::getline(std::cin, c.name);

    int hallCnt;
    std::cout << "How many halls to add now? ";std::cin >> hallCnt;

    for (int i = 0; i < hallCnt; ++i) {
        int num;
        std::cout << "Hall "<< i+1 <<" number: ";std::cin >> num;
        c.halls.push_back({num, {}});
    }
    cinemas.push_back(c);
    std::cout << "Cinema added.\n";
}

void updateCinema(std::vector<Cinema>& cinemas) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string oldName;
    std::cout << "Cinema to update: ";
    std::getline(std::cin, oldName);

    for (Cinema& c : cinemas) {
        if (c.name == oldName) {
            std::cout << "New name (leave empty to keep): ";
            std::string newName;
            std::getline(std::cin, newName);
            if (!newName.empty()) c.name = newName;

            int action;
            do {
                std::cout << "\nHall edit menu:\n1.Add hall\n2.Delete hall\n3.List halls\n4.Exit\nChoice: ";std::cin >> action;
                if (action == 1) {
                    int num; std::cout << "New hall number: "; std::cin >> num;
                    c.halls.push_back({num, {}});
                } else if (action == 2) {
                    int num; std::cout << "Hall number to delete: "; std::cin >> num;
                    for (auto it = c.halls.begin(); it != c.halls.end(); ++it)
                        if (it->hallNumber == num) { c.halls.erase(it); break; }
                } else if (action == 3) {
                    for (const Hall& h : c.halls) std::cout << "Hall " << h.hallNumber << "\n";
                }
            } while (action != 4);

            std::cout << "Cinema updated.\n";
            return;
        }
    }
    std::cout << "Cinema not found.\n";
}


void deleteCinema(std::vector<Cinema>& cinemas){
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string n; std::cout << "Cinema to delete: "; std::getline(std::cin, n);
    for (auto it = cinemas.begin(); it != cinemas.end(); ++it) if (it->name == n) { cinemas.erase(it); std::cout << "Deleted.\n"; return; }
    std::cout << "Not found.\n";
}

void addShow(std::vector<Cinema>& cinemas, std::vector<Movie>& movies){
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string cinemaName; std::cout << "Cinema: "; std::getline(std::cin, cinemaName);
    Cinema* cinema = nullptr; for (Cinema& c : cinemas) if (c.name == cinemaName) cinema = &c;
    if (!cinema) { std::cout << "Cinema not found.\n"; return; }

    int hallNum; std::cout << "Hall #: "; std::cin >> hallNum; Hall* hall = nullptr;
    for (Hall& h : cinema->halls) if (h.hallNumber == hallNum) hall = &h;
    if (!hall) { std::cout << "Hall not found.\n"; return; }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Show show; std::string mode;
    std::cout << "existing/new movie? : "; std::getline(std::cin, mode);
    if (mode == "existing") {
        for (size_t i = 0; i < movies.size(); ++i) std::cout << i + 1 << ". " << movies[i].title << "\n";
        int idx; std::cout << "Select # : "; std::cin >> idx;
        if (idx < 1 || idx > movies.size()) { std::cout << "Bad index.\n"; return; }
        show.movie = movies[idx - 1];
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else if (mode == "new") {
        show.movie = newMovie(); movies.push_back(show.movie);
    } else { std::cout << "Invalid.\n"; return; }

    std::cout << "Show time: "; std::getline(std::cin, show.time);
    show.seats = {{1,"silver",false},{2,"gold",false},{3,"platinum",false}};
    hall->shows.push_back(show); std::cout << "Show added.\n";
}

void updateShow(std::vector<Cinema>& cinemas, std::vector<Movie>& movies){
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string cinemaName; std::cout << "Cinema: "; std::getline(std::cin, cinemaName);
    Cinema* cinema = nullptr; for (Cinema& c : cinemas) if (c.name == cinemaName) cinema = &c;
    if (!cinema) { std::cout << "Cinema not found.\n"; return; }

    int hallNum; std::cout << "Hall #: "; std::cin >> hallNum; Hall* hall = nullptr;
    for (Hall& h : cinema->halls) if (h.hallNumber == hallNum) hall = &h;
    if (!hall) { std::cout << "Hall not found.\n"; return; }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string title, time; std::cout << "Movie title: "; std::getline(std::cin, title);
    std::cout << "Show time: "; std::getline(std::cin, time);

    for (Show& s : hall->shows) if (s.movie.title == title && s.time == time) {
        s.movie = newMovie(); std::cout << "New time: "; std::getline(std::cin, s.time);
        bool exists = false; for (const Movie& m : movies) if (m.title == s.movie.title) exists = true;
        if (!exists) movies.push_back(s.movie);
        std::cout << "Updated.\n"; return;
    }
    std::cout << "Show not found.\n";
}

void deleteShow(std::vector<Cinema>& cinemas){
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string cinemaName; std::cout << "Cinema: "; std::getline(std::cin, cinemaName);
    Cinema* cinema = nullptr; for (Cinema& c : cinemas) if (c.name == cinemaName) cinema = &c;
    if (!cinema) { std::cout << "Cinema not found.\n"; return; }

    int hallNum; std::cout << "Hall #: "; std::cin >> hallNum; Hall* hall = nullptr;
    for (Hall& h : cinema->halls) if (h.hallNumber == hallNum) hall = &h;
    if (!hall) { std::cout << "Hall not found.\n"; return; }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string title, time; std::cout << "Title: "; std::getline(std::cin, title);
    std::cout << "Time: "; std::getline(std::cin, time);

    for (auto it = hall->shows.begin(); it != hall->shows.end(); ++it)
        if (it->movie.title == title && it->time == time) { hall->shows.erase(it); std::cout << "Deleted.\n"; return; }
    std::cout << "Show not found.\n";
}

void bookTicket(std::vector<Cinema>& cinemas){
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string cinemaName; std::cout << "Cinema: "; std::getline(std::cin, cinemaName);
    Cinema* cinema = nullptr; for (Cinema& c : cinemas) if (c.name == cinemaName) cinema = &c;
    if (!cinema) { std::cout << "Cinema not found.\n"; return; }

    std::string movieTitle; std::cout << "Movie title: "; std::getline(std::cin, movieTitle);
    cinema->displayShows(movieTitle);

    int hallNum; std::cout << "Hall #: "; std::cin >> hallNum; Hall* hall = nullptr;
    for (Hall& h : cinema->halls) if (h.hallNumber == hallNum) hall = &h;
    if (!hall) { std::cout << "Hall not found.\n"; return; }

    Show* sh = nullptr; for (Show& s : hall->shows) if (s.movie.title == movieTitle) { sh = &s; break; }
    if (!sh) { std::cout << "Show not found.\n"; return; }

    for (const Seat& seat : sh->seats) std::cout << "[" << seat.number << ":" << (seat.booked ? 'X' : seat.type[0]) << "] ";
    std::cout << "\nX=Booked\n";

    int count; std::cout << "Seats to book: "; std::cin >> count;
    std::cout << "Choose seat numbers ";
    std::vector<int> sel; std::map<std::string, double> price{{"silver",10},{"gold",15},{"platinum",20}};
    double total = 0;
    for (int i = 0; i < count; ++i) {
        int num; std::cin >> num; bool ok = false;
        for (Seat& seat : sh->seats) if (seat.number == num && !seat.booked) { seat.booked = true; sel.push_back(num); total += price[seat.type]; ok = true; break; }
        if (!ok) { std::cout << "Seat " << num << " unavailable.\n"; for (int id : sel) for (Seat& s : sh->seats) if (s.number == id) s.booked = false; return; }
    }
    std::cout << "Total $" << total << "\nPay (1 credit online, 2 cash, 3 credit): ";
    int p; std::cin >> p;
    if (p < 1 || p > 3) { std::cout << "Cancelled.\n"; for (int id : sel) for (Seat& s : sh->seats) if (s.number == id) s.booked = false; return; }
    std::cout << "Booked!\n";
}

void adminMenu(std::vector<Cinema>& c, std::vector<Movie>& m){
    int ch;
    do {
        std::cout << "\n1.Add Movie 2.Delete Movie 3.Update Movie 4.Add Show 5.Delete Show 6.Update Show 7.Add Cinema 8.Delete Cinema 9.Update Cinema 10.Exit\nChoice: ";
        std::cin >> ch;
        switch (ch) {
            case 1: addMovie(m); break;
            case 2: removeMovie(m); break;
            case 3: updateMovie(m); break;
            case 4: addShow(c, m); break;
            case 5: deleteShow(c); break;
            case 6: updateShow(c, m); break;
            case 7: addCinema(c); break;
            case 8: deleteCinema(c); break;
            case 9: updateCinema(c); break;
            case 10: break;
            default: std::cout << "Invalid.\n";
        }
    } while (ch != 10);
}

void start(){
    std::vector<Cinema> cinemas;
    std::vector<Movie> movies;
    loadData(cinemas, movies);

    int mode; std::cout << "1.User 2.Admin\n"; std::cin >> mode;
    if (mode == 2) adminMenu(cinemas, movies);
    else {
        int ch;
        do {
            std::cout << "\n1.Search movie 2.View shows 3.Book 4.Exit\nChoice: ";
            std::cin >> ch;
            if (ch == 1) searchMovie(cinemas);
            else if (ch == 2) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string cinName;
                std::cout << "Cinema name (leave empty = all): ";
                std::getline(std::cin, cinName);

                bool found = false;
                for (const Cinema& c : cinemas) {
                    if (cinName.empty() || c.name == cinName) {
                        c.displayAllShows();
                        found = true;
                    }
                }
                if (!found) std::cout << "No such cinema.\n";
            }else if (ch == 2) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string cinName;
                std::cout << "Cinema name (leave empty = all): ";
                std::getline(std::cin, cinName);

                bool found = false;
                for (const Cinema& c : cinemas) {
                    if (cinName.empty() || c.name == cinName) {
                        c.displayAllShows();
                        found = true;
                    }
                }
                if (!found) std::cout << "No such cinema.\n";
            }
            else if (ch == 3) bookTicket(cinemas);
        } while (ch != 4);
    }
    saveData(cinemas);
}


