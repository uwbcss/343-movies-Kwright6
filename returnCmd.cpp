#include "returnCmd.h"
#include "classics.h"
#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;

// Constructor
ReturnCmd::ReturnCmd() : cmd('R') {}

// helper to Return movie

/*
  Take movie from customer and update stock
*/
void ReturnCmd::execute(MovieStore &store, const vector<string> &vs) const {
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

  if (genre == 'F') {
    // str = cmd id type genre title, year
    // vs[0] = B id D F title
    // vs[1] = year
    year = stoi(vs[1]);
    // Get full title (rest of iss)
    getline(iss, title);
    title = title.substr(title.find_first_not_of(' ')); // remove leading space
  }

  if (genre == 'D') {
    // str = cmd id type genre director, title
    // vs[0] = B id D D director
    // vs[1] = title
    title = vs[1];
    getline(iss, director);
    director = director.substr(
        director.find_first_not_of(' ')); // remove leading space
  }

  if (genre == 'C') {
    // str = cmd id type genre month year firstName lastName
    // vs[0] = B id D C month year firstName lastName
    // Use sstream to get all variables
    string firstName;
    string lastName;
    iss >> month >> year >> firstName >> lastName;
    majorActor = firstName + " " + lastName;
  }

  // Get movie
  Movie *movieToReturn = nullptr;
  const auto &movieList = inventory[genre - 'A'];
  if (!movieList.empty()) {
    for (Movie *movie : movieList) {
      // Comedy
      if (genre == 'F' && (movie->title == title && movie->getYear() == year)) {
        movieToReturn = movie;
        break;
      }

      // Drama
      if (genre == 'D' &&
          (movie->title == title && movie->director == director)) {
        movieToReturn = movie;
        break;
      }

      // Classic
      if (genre == 'C') {
        Classics *cMovie = dynamic_cast<Classics *>(movie);
        if (cMovie->month == month && cMovie->year == year &&
            cMovie->majorActor == majorActor) {
          movieToReturn = movie;
          break;
        }
      }
    }
  }

  // Return movie
  // output: Debug: Return <id> <fullName> movie->print()
  // cout << "Debug: Return " << id << " " << customer->getFullName() << " ";
  // movieToReturn->print();
  customer->returnMovie(movieToReturn);
  movieToReturn->stock++; // Update stock
}

#ifndef EXCLUDE_RETURNCMD

ReturnCmdFactory::ReturnCmdFactory() { registerType('R', this); }

Command *ReturnCmdFactory::makeCommand(const vector<string> &vs) const {
  assert(vs.size() == 2 || 1); // to avoid unused parameter warning
  return new ReturnCmd();
}

// creating the object registers the type at run time
ReturnCmdFactory theReturnCmdFactory;

#endif // EXCLUDE_RETURNCMD