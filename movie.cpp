#include "movie.h"
#include "movieFactory.h"
#include <iostream>
#include <map>

using namespace std;

/**
 * Storage place for the concrete movie factories
 * @return map
 */
map<char, MovieFactory *> &MovieFactory::getMap() {
  static map<char, MovieFactory *> factories;
  return factories;
}

// register a concrete factory with a given name
void MovieFactory::registerType(const char &type, MovieFactory *factory) {
  getMap().emplace(type, factory);
}

// find the corresponding movie factory and get factory to create the object
Movie *MovieFactory::create(const char &type, const vector<string> &vs) {
  auto &factories = getMap();
  if (factories.count(type) == 0) {
    cout << "Unknown movie type: " << type;
    return nullptr;
  }
  return factories.at(type)->makeMovie(vs);
}