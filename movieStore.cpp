#include "movieStore.h"
#include "classics.h"
#include "comedy.h"
#include "command.h"
#include "commandFactory.h"
#include "movieFactory.h"
#include <algorithm>
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

// getter for a modifiable moviesByType hashtable
vector<Movie *> (&MovieStore::getMoviesByType())[TABLE_SIZE] {
  return moviesByType;
}

// getter for customerList
unordered_map<int, Customer *> &MovieStore::getCustomerList() {
  return customerList;
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
      command->execute(*this, vs);
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

// function to sort movie inventory
void MovieStore::sortInventory() {
  // Sort Drama Vector
  std::sort(moviesByType['D' - 'A'].begin(), moviesByType['D' - 'A'].end(),
            [](Movie *a, Movie *b) {
              // sort by director, if same, sort by title
              return a->director < b->director ||
                     (a->director == b->director && a->title < b->title);
            });

  // Sort Comedy Vector
  std::sort(moviesByType['F' - 'A'].begin(), moviesByType['F' - 'A'].end(),
            [](Movie *a, Movie *b) {
              Comedy *fa = dynamic_cast<Comedy *>(a);
              Comedy *fb = dynamic_cast<Comedy *>(b);
              // sort by title, if same, sort by year
              return a->title < b->title ||
                     (a->title == b->title && fa->year < fb->year);
            });

  // Sort Classics Vector
  std::sort(moviesByType['C' - 'A'].begin(), moviesByType['C' - 'A'].end(),
            [](Movie *a, Movie *b) {
              Classics *ca = dynamic_cast<Classics *>(a);
              Classics *cb = dynamic_cast<Classics *>(b);
              // sort by year, if same, sort by month, if same, sort by
              // majorActor
              return ca->year < cb->year ||
                     (ca->year == cb->year && ca->month < cb->month) ||
                     (ca->year == cb->year && ca->month == cb->month &&
                      ca->majorActor < cb->majorActor);
            });
}