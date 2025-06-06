#include "customer.h"
#include <string>

using namespace std;

// Constructor
Customer::Customer(int id, const string &firstName, const string &lastName)
    : id(id), firstName(firstName), lastName(lastName) {}

// getter for ID
int Customer::getID() const { return id; }

// getter for name
string Customer::getFullName() const { return lastName + " " + firstName; }

void Customer::borrowMovie(Movie *movie) {
  // add movie to borrowedMovies
  borrowedMovies[movie->title] = movie;
}

void Customer::returnMovie(Movie *movie) {
  // remove movie from borrowedMovies
  borrowedMovies.erase(movie->title);
}

void Customer::getHistory() const {
  // TODO
}