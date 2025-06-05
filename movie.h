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
    protected:
        //string director, title;
    public:
        string director, title;
        int stock;
        virtual void print() const = 0; // each movie can print itself
        virtual ~Movie() = default;  // not really used in this case
};

#endif // MOVIE_H