#include "autocomplete.h"
#include <algorithm>
#include <fstream>

using namespace std;

void testBSTAll();

// Function reads file using name
void Autocomplete::readFile(const string &fileName) {
  ifstream ifs(fileName);
  int count;
  ifs >> count;
  vector<BSTMap::value_type> v;
  for (int i = 0; i < count; i++) {
    BSTMap::value_type t;
    ifs >> t.second;
    ifs.seekg(1, ios::cur);
    getline(ifs, t.first);
    // ifs >> t.first;
    v.push_back(t);
  }

  delete phrases;

  phrases = new BSTMap(v);

  ifs.close();
  phrases->rebalance();
}

// function sorts nodes by weight
bool Autocomplete::sortByWeight(BSTMap::value_type &a, BSTMap::value_type &b) {
  return a.second > b.second;
}

// function guesses/completes the key value
vector<BSTMap::value_type>
Autocomplete::complete(const BSTMap::key_type &prefix) const {
  auto v = phrases->getAll(prefix);
  sort(v.begin(), v.end(), sortByWeight);
  return v;
}
