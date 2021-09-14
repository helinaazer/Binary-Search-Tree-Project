#include "autocomplete.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
// Test case 1 for the auto complete using small.txt
void testAC01() {
  cout << "Starting AC test01" << endl;
  cout << "* Testing basic autocomplete" << endl;
  Autocomplete ac;
  ac.readFile("small.txt");
  auto v = ac.complete("hel");
  assert(v.size() == 2);
  assert(v[0].first == "help");
  assert(v[0].second == 20);
  assert(v[1].first == "hello");
  assert(v[1].second == 10);
  cout << "Ending tesAC01" << endl;
}

// Test case 2 for the auto complete using cities.txt
void testAC02() {
  cout << "Starting AC test02" << endl;
  cout << "* Testing cities autocomplete" << endl;
  Autocomplete ac;
  ac.readFile("cities.txt");
  auto v = ac.complete("Sea");
  assert(v.size() == 47);
  assert(v[0].first == "Seattle, Washington, United States");
  assert(v[0].second == 608660);
  assert(v[46].first == "Seabeck, Washington, United States");
  assert(v[46].second == 1105);
  cout << "Ending tesAC02" << endl;
}

// test case 3 for the auto complete using wiktionary.txt
void testAC03() {
  cout << "Starting AC test03" << endl;
  cout << "* Testing basic autocomplete" << endl;
  Autocomplete ac;
  ac.readFile("wiktionary.txt");
  auto v = ac.complete("tho");
  assert(v.size() == 16);
  assert(v[0].first == "those");
  assert(v[0].second == 87862100);
  assert(v[2].first == "though");
  assert(v[2].second == 57087700);
  cout << "Ending tesAC03" << endl;
}

// test case 4 for the autocomplete phrases
void testAC04() {
  cout << "Starting AC test04" << endl;
  cout << "* Testing that phrases is not nullptr" << endl;
  Autocomplete ac;
  ac.readFile("wiktionary.txt");
  ac.readFile("small.txt");
  cout << "Ending tesAC04" << endl;
}

// Calling all test functions
void testACAll() {
  testAC01();
  testAC02();
  testAC03();
  testAC04();
}