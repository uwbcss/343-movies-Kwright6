#include "classics.h"
#include <iostream>
#include <sstream>

using namespace std;

Classics::Classics(const vector<string> &vs) {
  if (vs.size() == 5) {
    // Initialize variables from vector<string>
    genre = vs[0][0];
    stock = stoi(vs[1]);
    director = vs[2];
    title = vs[3];
    // Use sstream to get variables separated by spaces in vs[4]
    istringstream iss(vs[4]);
    string firstName;
    string lastName;
    int mo;
    int yr;
    iss >> firstName >> lastName >> mo >> yr;
    // Initialize variables
    majorActor = firstName + " " + lastName;
    month = mo;
    year = yr;
  }
}

int Classics::getYear() const {
  return year;
}

void Classics::print() const {
  // C, 10, Victor Fleming, The Wizard of Oz, Judy Garland 7 1939
  // 1939 7, Judy Garland, Victor Fleming, The Wizard of Oz (10) - Classics
  // year month, majorActor, Director, Title (stock) - Classics
  cout << year << " " << month << ", " << majorActor << ", " << director << ", "
       << title << " (" << stock << ")" << " - Classics" << endl;
}

ClassicsFactory::ClassicsFactory() { registerType('C', this); }

Movie *ClassicsFactory::makeMovie(const vector<string> &vs) const {
  return new Classics(vs);
}

// creating the object registers the type at run time
ClassicsFactory theClassicsFactory;