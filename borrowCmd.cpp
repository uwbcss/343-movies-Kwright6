#include "borrowCmd.h"
#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;

// Constructor
BorrowCmd::BorrowCmd() : cmd('B') {} 

/*
  Give movie to customer and update stock
*/
void BorrowCmd::execute(MovieStore &store, const vector<string> &vs) const {
    // vs[0] = B id D genre title
    // vs[1] = year
    char cmd;
    int id;
    char type;
    char genre;
    string title;
    int year = stoi(vs[1]);
    // Use sstream to get variables separated by spaces in vs[0]
    istringstream iss(vs[0]);
    iss >> cmd >> id >> type >> genre;
    // Get full title (rest of iss)
    getline(iss, title);
    title = title.substr(title.find_first_not_of(' ')); // remove leading space

    // Get inventory and customerlist
    const auto &inventory = store.getMoviesByType();
    const auto &customers = store.getCustomerList();
    
    // Get customer
    Customer *customer = customers.at(id);

    cout << title << ", " << year << "     <-- 38:borrowCmd.cpp" << endl;
    // Get movie
    Movie *movieToBorrow;
    const auto &movieList = inventory[genre - 'A'];
    if (!movieList.empty()) {
        for (Movie *movie : movieList) {
            if (movie->title == title && movie->getYear() == year) {
            cout << movie->title << ", " << movie->getYear() << "     <-- 44:borrowCmd.cpp" << endl;
            movieToBorrow = movie;
            }
        }
    }

    // borrow movie
    customer->borrowMovie(movieToBorrow);

    // update stock
    movieToBorrow->stock--;

    // test print 
    movieToBorrow->print(); cout << "^-- 56:borrowCmd.cpp" << endl;
}

BorrowCmdFactory::BorrowCmdFactory() { registerType('B', this); }

Command *BorrowCmdFactory::makeCommand(const vector<string> &vs) const {
    assert(vs.size() == 2); // to avoid unused parameter warning  
    return new BorrowCmd();
}

// creating the object registers the type at run time
BorrowCmdFactory theBorrowCmdFactory;