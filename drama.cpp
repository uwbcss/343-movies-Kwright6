#include "drama.h"
#include <iostream>

using namespace std;

// Constuctor
Drama::Drama(const vector<string> &vs) {
  if (vs.size() == 5) {
    // Initialize variables from vector<string>
    genre = vs[0][0];
    stock = stoi(vs[1]);
    director = vs[2];
    title = vs[3];
    year = stoi(vs[4]);
  }
}

// getter for year
int Drama::getYear() const { return year; }

// print movie
void Drama::print() const {
  // D, 10, Barry Levinson, Good Morning Vietnam, 1988
  // Barry Levinson, Good Morning Vietnam, 1988 (10) - Drama
  // Director, Title, Year (stock) - Drama
  cout << director << ", " << title << ", " << year << " (" << stock << ")"
       << " - Drama" << endl;
}

// less than compare for sorting
bool Drama::lessThan(const Movie *other) const {
  return this->director < other->director ||
         (this->director == other->director && this->title < other->title);
}

#ifndef EXCLUDE_DRAMA

DramaFactory::DramaFactory() { registerType('D', this); }

Movie *DramaFactory::makeMovie(const vector<string> &vs) const {
  return new Drama(vs);
}

// creating the object registers the type at run time
DramaFactory theDramaFactory;

#endif // EXCLUDE_DRAMA