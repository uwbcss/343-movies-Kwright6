#include "customer.h"
#include <iostream>
#include <sstream>
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

  // update history
  history.push_back("Borrow " + movie->title);
}

void Customer::returnMovie(Movie *movie) {
  // Check that movie was borrowed
  if (borrowedMovies.find(movie->title) == borrowedMovies.end()) {
    // output:
    // ==========================
    // <fullName> could NOT return <title>, never borrowed:
    // ==========================
    // Failed to execute command: Return <fullName> <title>
    cout << "==========================" << endl;
    cout << getFullName() << " could NOT return "
         << movie->title << ", never borrowed:" << endl;
    cout << "==========================" << endl;
    cout << "Failed to execute command: Return " << getFullName()
         << " " << movie->title << endl;
    return;
  }

  // remove movie from borrowedMovies
  borrowedMovies.erase(movie->title);

  // update history
  history.push_back("Return " + movie->title);
}

void Customer::printHistory() const {
  // Check if no history
  if (history.empty()) {
    cout << "No history for " << getFullName() << endl;
    return;
  }

  // Print history
  string command;
  string title;
  for (string transaction : history) {
    istringstream iss(transaction);
    iss >> command;
    getline(iss, title);
    cout << command << " " << getFullName() << title << endl;
  }
}