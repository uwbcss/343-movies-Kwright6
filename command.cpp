#include "command.h"
#include "commandFactory.h"
#include <iostream>
#include <sstream>
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
Command *CommandFactory::create(const char &cmd, const vector<string> &vs) {
  auto &factories = getMap();
  if (factories.count(cmd) == 0) {
    cout << "Unknown command type: " << cmd << ", discarding line: ";
    if (vs.size() > 1) {
      for (int i = 1; i < vs.size(); i++) {
        cout << " " << vs[i];
      }
    } else {
      istringstream iss(vs[0]);
      string str;
      iss >> str; // remove invalid command
      getline(iss, str); // get rest of line
      cout << str;
    }
    cout << endl;
    return nullptr;
  }
  return factories.at(cmd)->makeCommand(vs);
}