#ifndef MOVIE_STORE_H
#define MOVIE_STORE_H

#include "movie.h"
#include <cassert>
#include <unordered_map>
#include <vector>

using namespace std;

class MovieStore {
    private:
        //unordered_map<char, vector<Movie *>> moviesByType; // easy container for movies
        // manual hashtable container for movies
        static const int TABLE_SIZE = 'Z' - 'A' + 1; // 'A' to 'Z' for up to 26 movie genres
        vector<Movie*> moviesByType[TABLE_SIZE]; // each bucket is a vector for each genre

        // hash function for container
        static int getBucket(char movieType) {
            assert(movieType >= 'A' && movieType <= 'Z'); // Ensure capital letter
            return movieType - 'A';
        }

    public:
        // getter for moviesByType hashtable
        const vector<Movie*> *getMoviesByType() const;
        
        // helper - get rid of spaces before and after string
        static string trimString(const string &str);

        // helper - split string into multiple based on delimiter
        static vector<string> splitString(const string &str, char delimiter = ',');

        // helper function for reading movies from file
        void readMoviesFromFile(const string &filename);

        // helper function for reading commands from file
        void readCommandsFromFile(const string &filename);

        void executeCommands(const string &filename);

        virtual ~MovieStore() = default; // not really used in this case
};

#endif // MOVIE_STORE_H