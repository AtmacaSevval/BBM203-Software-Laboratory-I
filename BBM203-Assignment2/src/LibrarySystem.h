//
// Created by EA on 30.11.2020.
//

#ifndef NEWASSIGNMENT2_LIBRARYSYSTEM_H
#define NEWASSIGNMENT2_LIBRARYSYSTEM_H

#include <string>

using namespace std;
extern std::ofstream outputFile;

class LibrarySystem {
public:
    LibrarySystem();
    ~LibrarySystem();
    void addUser(const int userId, const string userName);
    void deleteUser(const int userId);

    void addMovie(const int movieId, const string movieTitle, const int year);
    void deleteMovie(const int movieId);


    void checkoutMovie(const int movieId, const int userId);
    void returnMovie(const int movieId);

    void showAllMovies();
    void showMovie(const int movieId);
    void showUser(const int userId);

    int UserException(const int userId);
    int movieException(const int movieId);
    int checkedMovieException(const int movieId);
    void deleteChecked(const int movieId);
    void deleteMovieUser(const int userId);
    void addNotChecked(const int movieId, const string movieTitle, const int year);
};


#endif //NEWASSIGNMENT2_LIBRARYSYSTEM_H
