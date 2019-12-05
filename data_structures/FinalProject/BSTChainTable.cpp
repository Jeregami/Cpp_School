#include "BSTChainTable.hpp"
#include <iostream>
#include <cmath>

using namespace std;

BSTChainTable::BSTChainTable() {
  tableSize = 10009;
  table = new BSTNode*[tableSize];
  for (int i = 0; i < tableSize; i++) {
    table[i] = nullptr;
  }
}

BSTNode* BSTChainTable::createNode(int key) {
  BSTNode* newNode = new BSTNode;
  newNode->key = key;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

int BSTChainTable::hashFunction(int key) {
  return (key % tableSize);
}

BSTNode* BSTChainTable::BSTChainSearch(int key) {
  int index = hashFunction(key);
  BSTNode* searchNode = table[index];
  while (searchNode != NULL) {
    if (searchNode->key == key) {
      return searchNode;
    }
    else if (searchNode->key < key) {
      searchNode = searchNode->right;
    }
    else if (searchNode->key > key) {
      searchNode = searchNode->left;
    }
  }
  return NULL;
}


bool BSTChainTable::BSTChainInsert(int key) {
  if (BSTChainSearch(key) != NULL) {
    return false;
  }
  int index = hashFunction(key);
  if (table[index] == NULL) {
    table[index] = createNode(key);
    return true;
  }
  BSTNode* currentNode = table[index];
  BSTNode* previousNode = NULL;
  while (currentNode != NULL) {
    if (currentNode->key < key) {
      previousNode = currentNode;
      currentNode = currentNode->right;
    }
    else if (currentNode->key > key) {
      previousNode = currentNode;
      currentNode = currentNode->left;
    }
  }
  if (previousNode->key < key) {
    previousNode->right = createNode(key);
  }
  else if (previousNode->key > key) {
    previousNode->left = createNode(key);
  }
  return true;
}


bool BSTChainTable::BSTChainDelete(int key) {
  if (BSTChainSearch(key) == NULL) {
    return false;
  }
  int index = hashFunction(key);
  BSTNode* currentNode = table[index];
  BSTNode* previousNode = NULL;
  while (currentNode != NULL) {
    // Found the node to be deleted
    if (currentNode->key == key) {
      // Node being deleted is the root of the BST tree
      if (previousNode == NULL) {
        BSTNode* searchNode = currentNode;
        // tree only had the one root node
        if (searchNode->left == NULL && searchNode->right == NULL) {
          searchNode = NULL;
        }
        else {
          // make searchNode the minimum value on the right subtree
          if (searchNode->left == NULL) {
            previousNode = searchNode;
            searchNode = searchNode->right;
            while (searchNode->left != NULL) {
              previousNode = searchNode;
              searchNode = searchNode->left;
            }
            previousNode->left = searchNode->right;
          }
          // make searchNode the maximum value on the left subtree
          else {
            previousNode = searchNode;
            searchNode = searchNode->left;
            while (searchNode->right != NULL) {
              previousNode = searchNode;
              searchNode = searchNode->right;
            }
            previousNode->right = searchNode->left;
          }
          if (currentNode->left == searchNode) {
            searchNode->left = NULL;
          }
          else {
            searchNode->left = currentNode->left;
          }
          if (currentNode->right == searchNode) {
            searchNode->right == NULL;
          }
          else {
            searchNode->right = currentNode->right;
          }
        }
        table[index] = searchNode;
        delete currentNode;
        return true;
      }
      // Node cannot be the root
      // Node being deleted has no children
      if (currentNode->left == NULL && currentNode->right == NULL) {
        delete currentNode;
      }
      // Node being deleted has only right child
      else if (currentNode->left == NULL) {
        if (currentNode->key > previousNode->key) {
          previousNode->right = currentNode->right;
        }
        else {
          previousNode->left = currentNode->right;
        }
      }
      // Node being deleted has only left child
      else if (currentNode->right == NULL) {
        if (currentNode->key > previousNode->key) {
          previousNode->right = currentNode->left;
        }
        else {
          previousNode->left = currentNode->left;
        }
      }
      // Node being deleted has both left and right child
      else {
        BSTNode *searchNode = currentNode->left;
        BSTNode *searchNodePrev = NULL;
        while (searchNode->left != NULL) {
          searchNodePrev = searchNode;
          searchNode = searchNode->left;
        }
        searchNodePrev->left = searchNode->right;
        if (currentNode->key > previousNode->key) {
          previousNode->right = searchNode;
        }
        else {
          previousNode->left = searchNode;
        }
        if (currentNode->left == searchNode) {
          searchNode->left = NULL;
        }
        else {
          searchNode->left = currentNode->left;
        }
        if (currentNode->right == searchNode) {
          searchNode->right == NULL;
        }
        else {
          searchNode->right = currentNode->right;
        }
        delete currentNode;
      }
      return true;
    }
    else {
      previousNode = currentNode;
      if (currentNode->key < key) {
        currentNode = currentNode->right;
      }
      else if (currentNode->key > key) {
        currentNode = currentNode->left;
      }
    }
  }
}

int BSTChainTable::fillTable(vector <int> v, double loadFactor) {
  double numInserted = 0;
  int numDuplicates = 0;
  while ((numInserted / tableSize) < loadFactor) {
    if (BSTChainInsert(v[numInserted+numDuplicates]) == false) {
      numDuplicates++;
    }
    else {
      numInserted++;
    }
  }
  return numInserted;
}
