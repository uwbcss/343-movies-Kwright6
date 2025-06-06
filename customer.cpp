#include "customer.h"
#include <string>
#include <iostream>

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

  // update history
  history.push_back("Borrow " + movie->title);
}

void Customer::returnMovie(Movie *movie) {
  // remove movie from borrowedMovies
  borrowedMovies.erase(movie->title);

  // update history
  history.push_back("Return " + movie->title);
}

void Customer::getHistory() const {
  // TODO
}