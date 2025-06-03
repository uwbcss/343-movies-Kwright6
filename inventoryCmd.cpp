#include "inventoryCmd.h"
#include <cassert>
#include <iostream>

using namespace std;

void execute(/*pass reference to MovieStore&*/) {
    // display store inventory information by calling function with 
    // passed movie store object
}

InventoryCmdFactory::InventoryCmdFactory() { registerType('I', this); }

Command *InventoryCmdFactory::makeCommand(const vector<string> &vs) const {
    assert(vs.size() == 1);  // to avoid unused parameter warning
    return new InventoryCmd();
}

// creating the object registers the type at run time
InventoryCmdFactory theInventoryCmdFactory;