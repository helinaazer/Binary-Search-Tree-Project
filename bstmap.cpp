// Yusuf Pisan pisan@uw.edu
// 17 Jan 2021

// BST class
// Creates a BST to store values
// Uses Node which holds the data

#include "bstmap.h"
#include <cassert>

using namespace std;

// copy constructor
BSTMap::BSTMap(const BSTMap &bst) { root = copyNode(bst.root); }

// helper function for the copy constructor
BSTMap::Node *BSTMap::copyNode(Node *source) {
  if (source == nullptr) {
    return nullptr;
  }

  Node *newNode = new Node;
  newNode->data = source->data;
  newNode->left = copyNode(source->left);
  newNode->right = copyNode(source->right);

  return newNode;
}

// given an array of length n
// create a tree to have all items in that array
// with the minimum height (uses same helper as rebalance)
BSTMap::BSTMap(const vector<value_type> &v) {
  for (auto const &i : v) {
    insert(i);
  }
}

// destructor
BSTMap::~BSTMap() { clear(); }

// delete all nodes in tree
void BSTMap::clear() {
  clearHelper(root);
  root = nullptr;
}

// helper function for the clear function
void BSTMap::clearHelper(Node *source) {
  if (source == nullptr) {
    return;
  }

  clearHelper(source->left);
  clearHelper(source->right);
  delete source;
}

// true if no nodes in BST
bool BSTMap::empty() const { return root == nullptr; }

// Number of nodes in BST
int BSTMap::size() const { return _size; }

// true if item is in BST
bool BSTMap::contains(const key_type &key) const {
  return containsHelper(key, root);
}

// Helper function for the contains function
bool BSTMap::containsHelper(const key_type &key, Node *source) const {
  if (source == nullptr) {
    return false;
  }

  int comparison = source->data.first.compare(key);
  if (comparison == 0) {
    return true;
  }

  if (comparison > 0) {
    return containsHelper(key, source->right);
  }

  return containsHelper(key, source->left);
}

// If k matches the key returns a reference to its value
// If k does not match any key, inserts a new element
// with that key and returns a reference to its mapped value.
BSTMap::mapped_type &BSTMap::operator[](const key_type &k) {
  value_type *valuePtr = getValue(k, root);
  if (valuePtr == nullptr) {
    value_type t;
    t.first = k;
    Node *n = insert(t);
    return n->data.second;
  }
  return valuePtr->second;
}

// helper function for the operator[]
BSTMap::value_type *BSTMap::getValue(const key_type &key, Node *source) const {
  if (source == nullptr) {
    return nullptr;
  }

  int comparison = source->data.first.compare(key);
  if (comparison == 0) {
    return &source->data;
  }

  if (comparison > 0) {
    return getValue(key, source->right);
  }

  return getValue(key, source->left);
}

// function to get all nodes
vector<BSTMap::value_type> BSTMap::getAll(const key_type &k) const {
  vector<value_type> v;
  getAllHelper(v, root, k);
  return v;
}

// helper function for the getAll function
void BSTMap::getAllHelper(vector<value_type> &v, Node *source,
                          const key_type &k) const {
  if (source == nullptr) {
    return;
  }

  if (source->data.first.find(k) == 0) {
    v.push_back(source->data);
    getAllHelper(v, source->left, k);
    getAllHelper(v, source->right, k);
  } else {
    int comparison = source->data.first.compare(k);
    if (comparison > 0) {
      getAllHelper(v, source->left, k);
    } else {
      getAllHelper(v, source->right, k);
    }
  }
}

// 0 if empty, 1 if only root, otherwise
// height of root is max height of subtrees + 1
int BSTMap::height() const { return getHeight(root); }

// height of a Node, nullptr is 0, root is 1, static, no access to 'this'
// helper function to height(), used by printVertical
int BSTMap::getHeight(const Node *n) {
  if (n == nullptr) {
    return 0;
  }

  return 1 + max(getHeight(n->left), getHeight(n->right));
}

// same as contains, but returns 1 or 0
// compatibility with std::map
size_t BSTMap::count(const string &k) const {
  bool c = contains(k);
  if (c) {
    return 1;
  }
  return 0;
}

// inorder traversal: left-root-right
// takes a function that takes a single parameter of type T
void BSTMap::inorder(void visit(const value_type &item)) const {
  inorderHelper(root, visit);
}

// helper function for the inorder function
void BSTMap::inorderHelper(Node *source,
                           void visit(const value_type &item)) const {
  if (source == nullptr) {
    return;
  }
  inorderHelper(source->left, visit);
  visit(source->data);
  inorderHelper(source->right, visit);
}

// preorder traversal: root-left-right
void BSTMap::preorder(void visit(const value_type &item)) const {
  preorderHelper(root, visit);
}

// helper function for the preorder function
void BSTMap::preorderHelper(Node *source,
                            void visit(const value_type &item)) const {
  if (source == nullptr) {
    return;
  }
  visit(source->data);
  preorderHelper(source->left, visit);
  preorderHelper(source->right, visit);
}

// postorder traversal: left-right-root
void BSTMap::postorder(void visit(const value_type &item)) const {
  postorderHelper(root, visit);
}

// helper function for the postorder function
void BSTMap::postorderHelper(Node *source,
                             void visit(const value_type &item)) const {
  if (source == nullptr) {
    return;
  }
  postorderHelper(source->left, visit);
  postorderHelper(source->right, visit);
  visit(source->data);
}
// balance the BST by saving all nodes to a vector inorder
// and then recreating the BST from the vector
void BSTMap::rebalance() {
  vector<value_type> rebalanceVector;
  rebalanceHelper(root, rebalanceVector);
  clear();
  root = reinsertionHelper(rebalanceVector, 0, rebalanceVector.size());
}

// helper function for the rebalance function
void BSTMap::rebalanceHelper(Node *source,
                             vector<value_type> &rebalanceVector) {
  if (source == nullptr) {
    return;
  }
  rebalanceHelper(source->left, rebalanceVector);
  rebalanceVector.push_back(source->data);
  rebalanceHelper(source->right, rebalanceVector);
}

// helper function for the rebalance vector node
BSTMap::Node *BSTMap::reinsertionHelper(vector<value_type> &rebalanceVector,
                                        int start, int length) {
  if (length == 0) {
    return nullptr;
  }

  int mid = start + (length / 2);
  value_type &t = rebalanceVector.at(mid);
  Node *newNode = new Node;
  newNode->data = t;
  newNode->left = reinsertionHelper(rebalanceVector, start, mid - start);
  newNode->right =
      reinsertionHelper(rebalanceVector, mid + 1, length - mid + start - 1);
  return newNode;
}

// trees are equal if they have the same structure
// AND the same item values at all the nodes
bool BSTMap::operator==(const BSTMap &other) const {
  return equalsHelper(root, other.root);
}

// helper function for the == and != function
bool BSTMap::equalsHelper(Node *one, Node *two) const {
  if (one == nullptr) {
    return two == nullptr;
  }

  if (two == nullptr) {
    return false;
  }

  if (one->data.first != two->data.first) {
    return false;
  }

  if (one->data.second != two->data.second) {
    return false;
  }

  return equalsHelper(one->left, two->left) &&
         equalsHelper(one->right, two->right);
}

// not == to each other
bool BSTMap::operator!=(const BSTMap &other) const {
  return !equalsHelper(root, other.root);
}

// helper function for the operator[],
BSTMap::Node *BSTMap::insert(const value_type &newValue) {
  Node *newNode = new Node;
  newNode->data = newValue;
  newNode->left = nullptr;
  newNode->right = nullptr;

  if (root == nullptr) {
    root = newNode;
  } else {
    insertHelper(root, newNode);
  }
  _size++;
  return newNode;
}

// helper function for the insert function
void BSTMap::insertHelper(Node *source, Node *newNode) {
  int comparison = source->data.first.compare(newNode->data.first);
  if (comparison > 0) { // put it on the left
    if (source->left == nullptr) {
      source->left = newNode;
      return;
    }
    insertHelper(source->left, newNode);
  } else {
    if (source->right == nullptr) {
      source->right = newNode;
      return;
    }
    insertHelper(source->right, newNode);
  }
}
