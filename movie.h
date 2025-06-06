#ifndef MOVIE_H
#define MOVIE_H

#include <map>
#include <string>

using namespace std;
/**
 * Abstract Class
 * All Movies are derived from this class
 * Stores movie factories and creates Movie objects through static functions
 **/
class Movie {
    // All movies have stock, director, and title
    public:
        string director, title;
        int stock;
        virtual int getYear() const = 0;
        virtual void print() const = 0; // each movie can print itself
        virtual bool lessThan(const Movie* other) const = 0; // less than compare for sort
        virtual bool matches(int month, int year, string title, string director, 
            string majorActor) const = 0;  // compare for finding movies
        virtual ~Movie() = default;  // not really used in this case
};

#endif // MOVIE_H