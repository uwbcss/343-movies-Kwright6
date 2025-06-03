#ifndef COMMAND_H
#define COMMAND_H

#include "movieStore.h"
#include <map>
#include <string>

using namespace std;
/**
 * Abstract Class
 * All Commands are derived from this class
 * Stores command factories and creates Command objects through static functions
 **/
class Command {
    // All commands have...
    protected:
    public:
        // different commands do different things
        virtual void execute(MovieStore& store) const = 0;
        virtual ~Command() = default;  // not really used in this case
};

#endif // COMMAND_H