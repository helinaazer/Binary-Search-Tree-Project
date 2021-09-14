// /**
//  * Testing BST - Binary Search Tree functions
//  *
//  * This file has series of tests for BST
//  * Each test is independent and uses assert statements
//  * Test functions are of the form
//  *
//  *      test_netidXX()
//  *
//  * where netid is UW netid and XX is the test number starting from 01
//  *
//  * Test functions can only use the public functions from BST
//  * testBSTAll() is called from main in main.cpp
//  * testBSTAll calls all other functions
//  * @author Helina Azer and Geovanny Henein
//  * @date 1/23/2021
//  */

#include "bstmap.h"
#include <cassert>
#include <sstream>

using namespace std;

// global value for testing
// NOLINTNEXTLINE
stringstream globalSS;

// need to reset SS before calling this
void printer(const BSTMap::value_type &p) {
  globalSS << "[" << p.first << "=" << p.second << "]";
}

// Testing == and []
void test01() {
  cout << "Starting test01" << endl;
  cout << "* Testing ==, !=, [] and copy constructor" << endl;
  BSTMap b1;
  auto val = b1["hello"];
  assert(val == 0);
  b1["hello"] = 5;
  val = b1["hello"];
  assert(val == 5);
  b1["world"] = 42;

  BSTMap b2;
  assert(b1 != b2);
  b2["hello"] = 5;
  b2["world"] = 42;
  assert(b1 == b2);

  BSTMap b3(b2);
  assert(b1 == b3);
  cout << "Ending tes01" << endl;
}

// Testing traversal
void test02() {
  cout << "Starting test02" << endl;
  cout << "* Testing traversal" << endl;
  BSTMap b;
  b["x"] = 10;
  b["f"] = 5;
  b["b"] = 3;
  b["e"] = 4;
  b["z"] = 50;
  // cout << b;

  globalSS.str("");
  b.inorder(printer);
  string order = globalSS.str();
  assert(order == "[b=3][e=4][f=5][x=10][z=50]");

  globalSS.str("");
  b.preorder(printer);
  order = globalSS.str();
  assert(order == "[x=10][f=5][b=3][e=4][z=50]");

  globalSS.str("");
  b.postorder(printer);
  order = globalSS.str();
  assert(order == "[e=4][b=3][f=5][z=50][x=10]");
  cout << "Ending test02" << endl;
}

// Testing rebalance
void test03() {
  cout << "Starting test03" << endl;
  cout << "* Testing rebalance" << endl;
  BSTMap b;
  b["1"] = 1;
  b["2"] = 2;
  b["3"] = 3;
  b["4"] = 4;
  b["5"] = 5;
  b["6"] = 6;
  assert(b.height() == 6);
  // cout << b << endl;
  b.rebalance();
  assert(b.height() == 3);
  // cout << b << endl;
  b.clear();
  assert(b.height() == 0);
  cout << "Ending test03" << endl;
}

// testing helper functions: empty, size, clear, height, contains, and count
void test04() {
  cout << "Starting test04" << endl;
  cout << "* Testing Helper Functions: height(), size(), and count()" << endl;
  BSTMap b;
  b["1"] = 1;
  b["2"] = 2;
  b["3"] = 3;
  b["4"] = 4;
  b["5"] = 5;
  b["6"] = 6;
  b["7"] = 7;
  // testing height()
  assert(b.height() == 7);
  // testing size()
  assert(b.size() == 7);
  // testing count()
  assert(b.count("1") == 1);
  assert(b.count("8") == 0);
  cout << "Ending test04" << endl;
}

// testing helper functions: empty and clear, height, contains, and count
void test05() {
  cout << "Starting test05" << endl;
  cout << "* Testing Helper Functions: empty() and clear()" << endl;
  BSTMap b;
  b["1"] = 1;
  b["2"] = 2;
  b["3"] = 3;
  b["4"] = 4;
  b["5"] = 5;
  b["6"] = 6;
  b["7"] = 7;
  // testing empty()
  b.empty();
  // testing clear();
  b.clear();
  cout << "Ending test05" << endl;
}

// testing contains
void test06() {
  cout << "Starting test06" << endl;
  cout << "* Testing contains()" << endl;
  BSTMap b;
  b["1"] = 1;
  assert(b.contains("1") == true);
  assert(b.contains("4") == false);
  assert(b.contains("0") == false);
  cout << "Ending test06" << endl;
}

// testing !=
void test07() {
  cout << "Starting test07" << endl;
  cout << "* Testing !=" << endl;
  BSTMap b1;
  BSTMap b2;
  BSTMap b3;
  BSTMap b4;
  b1["hello"] = 10;
  b2["help"] = 20;
  b3["herd"] = 5;
  b4["herd"] = 7;
  assert(b1 != b2);
  assert(b3 != b4);
  cout << "Ending test07" << endl;
}

// Calling all test functions
void testBSTAll() {
  test01();
  test02();
  test03();
  test04();
  test05();
  test06();
  test07();
}