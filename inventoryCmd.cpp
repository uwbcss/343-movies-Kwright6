#include "inventoryCmd.h"
#include <cassert>
#include <iostream>

using namespace std;

InventoryCmd::InventoryCmd() : cmd('I') {} // Constructor

/*
  Print all movies in store Inventory
*/
void InventoryCmd::execute(MovieStore &store, const vector<string> &vs) const {
  assert(vs.size() == 1); // to avoid unused parameter warning
  static const int tablesize = 'Z' - 'A' + 1;
  const auto &inventory = store.getMoviesByType(); // get movies

  cout << "==========================" << endl; // formatting

  // Search through inventory for all movies
  for (int i = tablesize - 1; i >= 0; i--) {
    const auto &movieList = inventory[i];
    // If this genre has a list of movies
    if (!movieList.empty()) {
      for (const Movie *movie : movieList) {
        if (movie != nullptr) {
          // print movies
          movie->print();
        }
      }
    }
  }
}

#ifndef EXCLUDE_INVENTORYCMD

InventoryCmdFactory::InventoryCmdFactory() { registerType('I', this); }

Command *InventoryCmdFactory::makeCommand(const vector<string> &vs) const {
  assert(vs.size() == 1); // to avoid unused parameter warning
  return new InventoryCmd();
}

// creating the object registers the type at run time
InventoryCmdFactory theInventoryCmdFactory;

#endif  // EXCLUDE_INVENTORYCMD