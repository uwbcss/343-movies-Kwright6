#include "command.h"
#include "commandFactory.h"
#include <iostream>
#include <map>

using namespace std;

/**
 * Storage place for the concrete command factories
 * @return map
 */
map<char, CommandFactory *> &CommandFactory::getMap() {
  static map<char, CommandFactory *> factories;
  return factories;
}

// register a concrete factory with a given name
void CommandFactory::registerType(const char &type, CommandFactory *factory) {
  getMap().emplace(type, factory);
}

// find the corresponding command factory and get factory to create the object
Command *CommandFactory::create(const char &type, const vector<string> &vs) {
  auto &factories = getMap();
  if (factories.count(type) == 0) {
    cout << "Don't know how to create " << type << endl;
    return nullptr;
  }
  return factories.at(type)->makeCommand(vs);
}