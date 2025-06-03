#include "inventoryCmd.h"
#include <cassert>
#include <iostream>

using namespace std;

InventoryCmd::InventoryCmd() : cmd('I') {} // Constructor

void InventoryCmd::execute(MovieStore &store) const {
  // display store inventory information by calling function with
  // passed movie store object
  static const int tablesize = 'Z' - 'A' + 1;
  const auto &inventory = store.getMoviesByType();
  for (int i = 0; i < tablesize; i++) {
    const auto &movieList = inventory[i];
    if (!movieList.empty()) {
      for (const Movie *movie : movieList) {
        if (movie != nullptr) {
          // print movies
          cout << "execute[I]: " << movie->stock << ", " << movie->director
               << ", " << movie->title << endl;
          // movie->print(); (TODO)
        }
      }
    }
  }
}

InventoryCmdFactory::InventoryCmdFactory() { registerType('I', this); }

Command *InventoryCmdFactory::makeCommand(const vector<string> &vs) const {
  assert(vs.size() == 1); // to avoid unused parameter warning
  return new InventoryCmd();
}

// creating the object registers the type at run time
InventoryCmdFactory theInventoryCmdFactory;