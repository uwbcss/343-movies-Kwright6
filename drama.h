#ifndef DRAMA_H
#define DRAMA_H

/**
 * Drama class, Drama is a Movie
 */

#include "movie.h"
#include "movieFactory.h"
#include <vector>

class Drama : public Movie {
    private:
        char genre;  // 'D'
    public:
        int year;

        // Constructor
        explicit Drama(const vector<string>& vs);

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
 * Creating DramaFactory to make Drama objects
 * DramaFactory object will register itself later and get stored in Movie class
 */
class DramaFactory : public MovieFactory {
public:
  DramaFactory();
  Movie *makeMovie(const vector<string>& vs) const override;
};

#endif // DRAMA_H