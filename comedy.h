#ifndef COMEDY_H
#define COMEDY_H

/**
 * Comedy class, Comedy is a Movie
 */

#include "movie.h"
#include "movieFactory.h"
#include <vector>

class Comedy : public Movie {
    private:
        char genre; // 'F'
    public:
        int year;

        // Constructor
        explicit Comedy(const vector<string>& vs);

        // getter for year
        int getYear() const override;

        void print() const override;
};

/**
 * Creating ComedyFactory to make Comedy objects
 * ComedyFactory object will register itself later and get stored in Movie class
 */
class ComedyFactory : public MovieFactory {
public:
  ComedyFactory();
  Movie *makeMovie(const vector<string>& vs) const override;
};

#endif // COMEDY_H