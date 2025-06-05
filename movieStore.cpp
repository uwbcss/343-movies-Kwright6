#include "movieStore.h"
#include "command.h"
#include "commandFactory.h"
#include "movieFactory.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// Destructor
MovieStore::~MovieStore() {
  // Delete all movies in inventory
  for (int i = 0; i < TABLE_SIZE; i++) {
    const auto &movieList = moviesByType[i];
    // If this list has movies
    if (!movieList.empty()) {
      for (Movie *movie : movieList) {
        delete movie;
      }
    }
  }

  // Delete all customers in customerList
  for (auto &pair : customerList) {
    delete pair.second;
  }
}

// getter for moviesByType hashtable
const vector<Movie *> *MovieStore::getMoviesByType() const {
  return moviesByType;
}

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

// helper function for reading movies from file
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

    // ignoring other parameters
    Movie *movie = MovieFactory::create(genre, vs);
    if (movie == nullptr) { // Discard line if nullptr
      // reconnect string minus the command
      string trimmed;
      for (int i = 1; i < vs.size(); ++i) {
        if (i > 1) {
          trimmed += ", ";
        }
        trimmed += vs[i];
      }
      cout << ", discarding line:  " << trimmed << endl;
      continue;
    }
    // add movie to inventory
    moviesByType[getBucket(genre)].push_back(movie);
  }
}

// helper function for reading & executing commands from file
void MovieStore::readCommandsFromFile(const string &filename) {
  vector<Command *> commands;
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

    char cmd = vs[0][0]; // take the first character as command

    // create self-registered command of correct command type
    Command *command = CommandFactory::create(cmd, vs);
    if (command != nullptr) { // ensure command was recognized
      // execute command and pass a reference to this store
      command->execute(*this);
      cout << "==========================" << endl;
    }
    delete command;
  }
}

void MovieStore::executeCommands(const string &filename) {
  // Read commands from file and execute them
  readCommandsFromFile(filename);
}

void MovieStore::readCustomersFromFile(const string &filename) {
  ifstream fs(filename);
  if (!fs.is_open()) {
    cerr << "Could not open file: " << filename << endl;
    return;
  }

  string str;
  while (getline(fs, str) && !str.empty()) {
    istringstream iss(str);
    int id;
    string firstName;
    string lastName;
    iss >> id >> lastName >> firstName;

    // create new customer
    Customer *customer = new Customer(id, firstName, lastName);

    // add customer to customer list
    customerList[id] = customer;
  }
}