/**
 * Testing ass4 movie store functions
 *
 * @author Yusuf Pisan
 * @date 19 Jan 2019
 */
#include "movie.h"
#include "movieFactory.h"
#include "movieStore.h"
#include "movieFactory.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

void testStore1() {
  cout << "Start testStore1" << endl;
  // Should do something more, but lets just read files
  // since each implementation will
  string cfile = "testcommands-1.txt";
  stringstream out;
  ifstream fs(cfile);
  assert(fs.is_open());
  char commandType;
  string discard;
  while (fs >> commandType) {
    out << commandType;
    getline(fs, discard);
  }
  fs.close();
  string result = "IHHBRIBBIH";
  assert(out.str() == result);
  cout << "End testStore1" << endl;
}

// helper - get rid of spaces before and after string
string trimString(const string &str) {
  return str.substr(str.find_first_not_of(' '), str.find_last_not_of(' ') + 1);
}

// helper - split string into multiple based on delimiter
vector<string> splitString(const string &str, char delimiter = ',') {
  vector<string> tokens;
  string token;
  istringstream tokenStream(str);
  while (getline(tokenStream, token, delimiter)) {
    tokens.push_back(trimString(token));
  }
  return tokens;
}

void testStore2() {
  cout << "Start testStore2" << endl;

  string cfile = "testMovieData.txt";
  stringstream out;

  ifstream fs(cfile);
  assert(fs.is_open());

  string str;
  while (getline(fs, str) && !str.empty()) {
    vector<string> vs = splitString(str); // split string into tokens
    if (vs.empty()) {
      continue;
    } // check if empty

    char genre = vs[0][0]; // take the first character as movie genre
    out << vs[0];

    // ignoring other pet parameters for this example
    Movie *movie = MovieFactory::create(genre, vs);
  }
  fs.close();
  assert(out.str() == "DCF");
  cout << "End testStore2" << endl;
}

void testStoreFinal() {
  cout << "=====================================" << endl;
  cout << "Start testStoreFinal" << endl;

  MovieStore store;  // create store

  // initialize the contents of the inventory from file
  store.readMoviesFromFile("testMovieData.txt");
  cout << "==========================" << endl;

  // initialize the customer list from another file (TODO)

  // process an arbitrary sequence of commands from a third file (TODO)
  store.executeCommands("testcommands-1.txt");

  cout << "End testStoreFinal" << endl;
  cout << "=====================================" << endl;
}

void testAll() {
  testStore1();
  testStore2();
  testStoreFinal();
}
