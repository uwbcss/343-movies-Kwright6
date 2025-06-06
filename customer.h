#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "movie.h"
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Customer {
    private:
        int id; // ####
        string firstName;
        string lastName;
        unordered_map<string, Movie*> borrowedMovies; // movie map <Title, Movie>
        vector<string> history; // string format = "cmd title" ex: "Borrow Unforgiven"
    public:
        // Constructor
        Customer(int id, const string &firstName, const string &lastName);

        // getter for ID
        int getID() const;

        // getter for name
        string getFullName() const;

        void borrowMovie(Movie* movie);

        void returnMovie(Movie* movie);

        void printHistory() const;
};

#endif // CUSTOMER_H