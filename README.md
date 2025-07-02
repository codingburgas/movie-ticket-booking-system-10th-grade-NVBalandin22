<h1 align="center">Movie Ticket Booking System</h1>

<hr>

<h2>Overview</h2>
<p>The <strong>Movie Ticket Booking System</strong> is a C++ console application designed for booking movie tickets and managing cinema operations. It offers functionality for users to search for movies, view showtimes, book seats, and allows administrators to manage movies, cinemas, halls, and shows, with robust notifications management.</p>

<hr>

<h2>Features</h2>
<ul>
  <li><strong>Multiple Cinemas & Halls</strong>: Manage multiple cinemas, each with several halls.</li>
  <li><strong>Movie Management</strong>:
    <ul>
      <li>Add new movies.</li>
      <li>Update existing movies.</li>
      <li>Delete movies.</li>
    </ul>
  </li>
  <li><strong>Show Management</strong>:
    <ul>
      <li>Add, update, and remove showtimes.</li>
    </ul>
  </li>
  <li><strong>Seat Selection & Pricing</strong>:
    <ul>
      <li>Silver, Gold, Platinum seat categories.</li>
      <li>Individual seat booking and status management.</li>
    </ul>
  </li>
  <li><strong>Advanced Search</strong>:
    <ul>
      <li>Search movies by title, genre, language, or release date.</li>
      <li>Display associated cinema, hall, and showtime details.</li>
    </ul>
  </li>
  <li><strong>Notifications System</strong>:
    <ul>
      <li>New movie releases, bookings, and cancellations notifications.</li>
      <li>Notifications stored and marked as read after viewing.</li>
    </ul>
  </li>
  <li><strong>Admin Authentication</strong>:
    <ul>
      <li>Secure login (admin@gmail.com / manager4365).</li>
      <li>Automatic data deletion after three failed attempts.</li>
    </ul>
  </li>
</ul>

<hr>

<h2>Prerequisites</h2>
<ul>
  <li><strong>C++17 compiler (GCC/Clang/MSVC)</strong></li>
  <li><strong>CMake (3.15+)</strong></li>
  <li><strong>Git (for version control)</strong></li>
</ul>

<hr>

<h2>How to Build and Run</h2>
<h3>1. Clone Repository</h3>

```bash
git clone https://github.com/codingburgas/movie-ticket-booking-system-10th-grade-NVBalandin22.git
cd movie-ticket-booking-system
```

<h3>2. Build with CMake</h3>

```bash
cmake -S . -B build
cmake --build build
```

<h3>3. Run Application</h3>

```bash
cd build
./MovieBookingSystem # On Windows: MovieBookingSystem.exe
```

<hr>

<h2>File Structure</h2>
<pre>
.
├── data/
│   ├── data.txt (cinema and show data)
│   └── notifications.txt (notification data)
├── include/
│   ├── cinema.h
│   ├── functions.h
│   ├── movie.h
│   └── show.h
├── src/
│   ├── cinema.cpp
│   ├── functions.cpp
│   ├── main.cpp
│   ├── movie.cpp
│   └── show.cpp
├── CMakeLists.txt
└── README.md
</pre>

<hr>

<h2>Technologies Used</h2>
<ul>
  <li><strong>C++17</strong></li>
  <li><strong>CMake</strong></li>
  <li><strong>Git & GitHub</strong></li>
</ul>

<hr>

<h2>Done by Nikita Balandin 10-V</h2>

<hr>

<h2>Future Enhancements</h2>
<ul>
  <li>Implement graphical user interface.</li>
  <li>Switch data storage to database format.</li>
  <li>Add automated unit tests.</li>
  <li>Continuous Integration via GitHub Actions.</li>
</ul>
