#ifndef MOVIE_FACTORY_H
#define MOVIE_FACTORY_H

#include <map>
#include <string>
#include <vector>

using namespace std;

// forward declaration
class Movie;

// Abstract MovieFactory where each subclass of Movie needs its own concrete version
class MovieFactory {  // implemented in movie
public:
  virtual Movie *makeMovie(const vector<string>& vs) const = 0;

  // find the corresponding movie factory and get factory to create the object
  static Movie *create(const char &type, const vector<string>& vs);

protected:
  // register a concrete factory with a given name
  static void registerType(const char &type, MovieFactory *factory);

private:
  /**
   * Storage place for the concrete movie factories
   * @return map
   */
  static map<char, MovieFactory *> &getMap();
};

#endif // MOVIE_FACTORY_H
