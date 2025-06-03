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

    // Test Output//
    cout << genre << ", " << stock << ", " << director << ", " << title << ", "
         << year << endl;
  }
}

DramaFactory::DramaFactory() { registerType('D', this); }

Movie *DramaFactory::makeMovie(const vector<string> &vs) const {
  return new Drama(vs);
}

// creating the object registers the type at run time
DramaFactory theDramaFactory;