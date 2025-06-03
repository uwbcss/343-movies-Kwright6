#include "movieStore.h"
#include "movieFactory.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// MovieStore::~MovieStore() {
//   for (auto& vec : moviesByType)
//     for (Movie* movie : vec)
//       delete movie;
// }

// helper - get rid of spaces before and after string
string MovieStore::trimString(const string &str) {
  return str.substr(str.find_first_not_of(' '), str.find_last_not_of(' ') + 1);
}

// helper - split string into multiple based on delimiter
vector<string> MovieStore::splitString(const string &str, char delimiter) {
  vector<string> tokens;
  string token;
  istringstream tokenStream(str);
  while (getline(tokenStream, token, delimiter)) {
    tokens.push_back(trimString(token));
  }
  return tokens;
}

// helper function for reading from file
void MovieStore::readMoviesFromFile(const string &filename) {
  vector<Movie *> movies;
  ifstream fs(filename);
  if (!fs.is_open()) {
    cerr << "Could not open file: " << filename << endl;
    return;
  }

  string str;
  while (getline(fs, str) && !str.empty()) {
    vector<string> vs = splitString(str);
    if (vs.empty()) {
      continue;
    } // check if empty

    char genre = vs[0][0]; // take the first character as movie genre

    // ignoring other pet parameters for this example
    Movie *movie = MovieFactory::create(genre, vs);
    if (movie != nullptr) {
      moviesByType[getBucket(genre)].push_back(movie);
    }
  }
}

void MovieStore::executeCommands(const string &filename) {
  // Read commands from file and execute them
}