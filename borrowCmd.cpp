#include "borrowCmd.h"
#include "classics.h"
#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;

// Constructor
BorrowCmd::BorrowCmd() : cmd('B') {}

// helper to borrow movie

/*
  Give movie to customer and update stock
*/
void BorrowCmd::execute(MovieStore &store, const vector<string> &vs) const {
  char cmd;
  char type;
  char genre;
  int id;
  int month;
  int year;
  string title;
  string director;
  string majorActor;

  // vs[0] = cmd id type genre
  istringstream iss(vs[0]);
  iss >> cmd >> id >> type >> genre;

  // Get inventory and customerlist
  const auto &inventory = store.getMoviesByType();
  const auto &customers = store.getCustomerList();

  // Get customer
  Customer *customer = nullptr;
  auto it = customers.find(id);
  if (it != customers.end()) {
    // Save valid customer
    customer = it->second;
  }

  // Check for Valid Movie Type
  if (genre != 'F' && genre != 'D' && genre != 'C') {
    // output: Invalid movie type <type>, discarding line:  2 1971 Malcolm
    // McDowell
    string str;
    getline(iss, str);
    cout << "Invalid movie type " << genre << ", discarding line: " << str
         << endl;
    return;
  }

  if (genre == 'F') {
    // Check for Valid Type
    if (type != 'D') {
      // output: Invalid media type <type>, discarding line:  F Fargo, 1996
      string str;
      getline(iss, str);
      cout << "Invalid media type " << type << ", discarding line: " << str
           << ", " << vs[1] << endl;
      return;
    }

    // Check for valid customer
    if (customer == nullptr) {
      // Invalid Customer
      // output: Invalid customer ID <id>, discarding line:  D F You've Got
      // Mail, 1998"
      istringstream iss(vs[0]);
      string str;
      iss >> cmd >> id;
      getline(iss, str);
      cout << "Invalid customer ID " << id << ", discarding line: " << str
           << ", " << vs[1] << endl;
      return;
    }

    // str = cmd id type genre title, year
    // vs[0] = B id D F title
    // vs[1] = year
    year = stoi(vs[1]);
    // Get full title (rest of iss)
    getline(iss, title);
    title = title.substr(title.find_first_not_of(' ')); // remove leading space
  }

  if (genre == 'D') {
    // Check for Valid Type
    if (type != 'D') {
      // output: Invalid media type <type>, discarding line:  D director, title
      string str;
      getline(iss, str);
      cout << "Invalid media type " << type << ", discarding line: " << str
           << ", " << vs[1] << endl;
      return;
    }

    // Check for valid customer
    if (customer == nullptr) {
      // Invalid Customer
      // output: Invalid customer ID <id>, discarding line:  D D director, title
      istringstream iss(vs[0]);
      string str;
      iss >> cmd >> id;
      getline(iss, str);
      cout << "Invalid customer ID " << id << ", discarding line: " << str
           << ", " << vs[1] << endl;
      return;
    }

    // str = cmd id type genre director, title
    // vs[0] = B id D D director
    // vs[1] = title
    title = vs[1];
    getline(iss, director);
    director = director.substr(
        director.find_first_not_of(' ')); // remove leading space
  }

  if (genre == 'C') {
    // Check for Valid Type
    if (type != 'D') {
      // output: Invalid media type <type>, discarding line:  C 5 1940 Katherine
      // Hepburn
      string str;
      getline(iss, str);
      cout << "Invalid media type " << type << ", discarding line: " << str
           << endl;
      return;
    }

    // Check for valid customer
    if (customer == nullptr) {
      // Invalid Customer
      // output: Invalid customer ID <id>, discarding line:  D C release date
      // director
      istringstream iss(vs[0]);
      string str;
      iss >> cmd >> id;
      getline(iss, str);
      cout << "Invalid customer ID " << id << ", discarding line: " << str
           << endl;
      return;
    }

    // str = cmd id type genre month year firstName lastName
    // vs[0] = B id D C month year firstName lastName
    // Use sstream to get all variables
    string firstName;
    string lastName;
    iss >> month >> year >> firstName >> lastName;
    majorActor = firstName + " " + lastName;
  }

  // Get movie
  Movie *movieToBorrow = nullptr;
  const auto &movieList = inventory[genre - 'A'];
  if (!movieList.empty()) {
    for (Movie *movie : movieList) {
      // Comedy
      if (genre == 'F' && (movie->title == title && movie->getYear() == year)) {
        movieToBorrow = movie;
        break;
      }

      // Drama
      if (genre == 'D' &&
          (movie->title == title && movie->director == director)) {
        movieToBorrow = movie;
        break;
      }

      // Classic
      if (genre == 'C') {
        Classics *cMovie = dynamic_cast<Classics *>(movie);
        if (cMovie->month == month && cMovie->year == year &&
            cMovie->majorActor == majorActor) {
          movieToBorrow = movie;
          break;
        }
      }
    }
  }

  // Check if movie is invalid (bogus title) (todo: output)
  if (movieToBorrow == nullptr) {
    // output: Invalid movie for customer <fullName>, discarding line:"
    string str;
    getline(iss, str);
    cout << "Invalid movie for customer " << customer->getFullName()
         << ", discarding line: " << endl;
    return;
  }

  // Check stock
  if (movieToBorrow->stock > 0) {
    // Borrow movie
    customer->borrowMovie(movieToBorrow);
    // output: Debug: Borrow <id> <fullName> movie->print()
    cout << "Debug: Borrow " << id << " " << customer->getFullName() << " ";
    movieToBorrow->print();
    movieToBorrow->stock--; // Update stock
  } else {
    // output: Debug: Borrow <id> <fullName> movie->print() *with 0 stock*
    cout << "Debug: Borrow " << id << " " << customer->getFullName() << " ";
    movieToBorrow->print();
    // output:
    // ==========================
    // <fullName> could NOT borrow <title>, out of stock:
    // ==========================
    // Failed to execute command: Borrow <fullName> <title>
    cout << "==========================" << endl;
    cout << customer->getFullName() << " could NOT borrow "
         << movieToBorrow->title << ", out of stock:" << endl;
    cout << "==========================" << endl;
    cout << "Failed to execute command: Borrow " << customer->getFullName()
         << " " << movieToBorrow->title << endl;
  }
}

BorrowCmdFactory::BorrowCmdFactory() { registerType('B', this); }

Command *BorrowCmdFactory::makeCommand(const vector<string> &vs) const {
  assert(vs.size() == 2 || 1); // to avoid unused parameter warning
  return new BorrowCmd();
}

// creating the object registers the type at run time
BorrowCmdFactory theBorrowCmdFactory;