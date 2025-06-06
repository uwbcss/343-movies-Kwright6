#ifndef CLASSICS_H
#define CLASSICS_H

/**
 * Classics class, Classics are Movies
 */

#include "movie.h"
#include "movieFactory.h"
#include <vector>

class Classics : public Movie {
    private:
        char genre; // "C"
    public:
        int month;
        int year;
        string majorActor;
        
        // Constructor
        explicit Classics(const vector<string> &vs);

        // getter for year
        int getYear() const override;

        // print movie
        void print() const override;

        // less than compare for sorting
        bool lessThan(const Movie* other) const override;

        // compare for finding movie
        bool matches(int month, int year, string title, string director, 
            string majorActor) const override;
};

/**
 * Creating ClassicFactory to make Classic objects
 * ClassicFactory object will register itself later and get stored in Movie class
 */

 class ClassicsFactory : public MovieFactory {
    public:
        ClassicsFactory(); // constructor
        Movie *makeMovie(const vector<string> &vs) const override;
 };

#endif // CLASSICS_H
