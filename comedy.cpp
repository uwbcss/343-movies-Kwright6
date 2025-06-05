#include "comedy.h"
#include <iostream>

using namespace std;

Comedy::Comedy(const vector<string> &vs) {
  if (vs.size() == 5) {
    // Initialize variables from vector<string>
    genre = vs[0][0];
    stock = stoi(vs[1]);
    director = vs[2];
    title = vs[3];
    year = stoi(vs[4]);
  }
}

void Comedy::print() const {
  // F, 10, Nora Ephron, Sleepless in Seattle, 1993
  // Sleepless in Seattle, 1993, Nora Ephron (10) - Comedy
  // Title, Year, Director (stock) - Comedy
  cout << title << ", " << year << ", " << director << " (" << stock << ")"
       << " - Comedy" << endl;
}

ComedyFactory::ComedyFactory() { registerType('F', this); }

Movie *ComedyFactory::makeMovie(const vector<string> &vs) const {
  return new Comedy(vs);
}

// creating the object registers the type at run time
ComedyFactory theComedyFactory;