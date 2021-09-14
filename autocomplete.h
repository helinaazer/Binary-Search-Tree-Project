#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

#include "bstmap.h"

using namespace std;

class Autocomplete {
public:
  // autocomplete constructor had to be implemented in order to fix clang-tidy
  // warning
  Autocomplete() = default;
  Autocomplete(const Autocomplete &other) = delete;
  Autocomplete(Autocomplete &&other) = delete;
  Autocomplete &operator=(const Autocomplete &other) = delete;
  // move assignment not allowed
  Autocomplete &operator=(Autocomplete &&other) = delete;

  // function that reads the file
  void readFile(const string &fileName);
  // function guesses/completes the key value
  vector<BSTMap::value_type> complete(const string &prefix) const;
  // autocomplete destructor. It had to be public in order to avoid memory leak.
  virtual ~Autocomplete() { delete phrases; }

private:
  // BST of phrases and their frequency
  BSTMap *phrases = nullptr;

  // sorter
  bool static sortByWeight(BSTMap::value_type &a, BSTMap::value_type &b);
};

#endif // AUTOCOMPLETE_H
