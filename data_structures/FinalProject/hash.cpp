#include "hash.hpp"
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;


HashTable::HashTable() {
  tableSize = 10009;
  table1 = new node*[tableSize];
  table2 = new node*[tableSize];
  for (int i = 0; i < tableSize; i++) {
    table1[i] = nullptr;
    table2[i] = nullptr;
  }
}

HashTable::HashTable(int newTableSize) {
  tableSize = newTableSize;
  table1 = new node*[tableSize];
  table2 = new node*[tableSize];
  for (int i = 0; i < tableSize; i++) {
    table1[i] = nullptr;
    table2[i] = nullptr;
  }
}

node* HashTable::createNode(int key, node* next) {
  node* newNode = new node;
  newNode->key = key;
  newNode->next = next;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

int HashTable::hashFunction1(int key) {
  return (key % tableSize);
}

int HashTable::hashFunction2(int key) {
  return floor(key / tableSize);
}

void HashTable::printLLChainTable() {
  for (int i = 0; i < tableSize; i++) {
    node *currentNode = table1[i];
    if (currentNode != NULL) {
      cout << i << "|| ";
      while (currentNode != NULL) {
        cout << currentNode->key << " ";
        currentNode = currentNode->next;
      }
      cout << endl;
    }
  }
}

void printTree(node *currentNode) {
  if (currentNode != NULL) {
    printTree(currentNode->left);
    cout << currentNode->key << " ";
    printTree(currentNode->right);
  }
  else {
    return;
  }
}

void HashTable::printBSTChainTable() {
  for (int i = 0; i < tableSize; i++) {
    node *currentNode = table1[i];
    if (currentNode != NULL) {
      node *BSTNode = table1[i];
      cout << i << "|| ";
      printTree(BSTNode);
      cout << endl;
    }
  }
}

void HashTable::printLinearTable() {
  for (int i = 0; i < tableSize; i++) {
    node *currentNode = table1[i];
    if (currentNode != NULL && currentNode->key != -1) {
      cout << i << "|| " << currentNode->key << endl;
    }
  }
}

void HashTable::printCuckooTable() {
  cout << "Table 1:" << endl;
  for (int i = 0; i < tableSize; i++) {
    node *currentNode = table1[i];
    if (currentNode != NULL && currentNode->key != -1) {
      cout << i << "|| " << currentNode->key << endl;
    }
  }
  cout << "Table 2:" << endl;
  for (int i = 0; i < tableSize; i++) {
    node *currentNode = table2[i];
    if (currentNode != NULL && currentNode->key != -1) {
      cout << i << "|| " << currentNode->key << endl;
    }
  }
}

// Collision Mechanisms

// Chaining with a Linked List


node* HashTable::linkedListChainSearch(int key, int whichTable) {
  node* *table;
  int index;
  if (whichTable == 1) {
    table = table1;
    index = hashFunction1(key);
  }
  else {
    table = table2;
    index = hashFunction2(key);
  }
  node* searchNode = table[index];
  while (searchNode != NULL) {
    if (searchNode->key == key) {
      return searchNode;
    }
    searchNode = searchNode->next;
  }
  return NULL;
}


bool HashTable::linkedListChainInsert(int key, int whichTable) {
  if (linkedListChainSearch(key, whichTable) != NULL) {
    return false;
  }
  node* *table;
  int index;
  if (whichTable == 1) {
    table = table1;
    index = hashFunction1(key);
  }
  else {
    table = table2;
    index = hashFunction2(key);
  }
  if (table[index] == NULL) {
      table[index] = createNode(key, NULL);
      return true;
  }
  node* currentNode = table[index];
  node* previousNode = NULL;
  while (currentNode != NULL) {
    // Found the spot where the new node should go
    if (currentNode->key > key) {
      if (previousNode == NULL) {
        table[index] = createNode(key, currentNode);
      }
      else {
        previousNode->next = createNode(key, currentNode);
      }
      break;
    }
    else {
      previousNode = currentNode;
      currentNode = currentNode->next;
    }
  }
  if (currentNode == NULL) {
    previousNode->next = createNode(key, NULL);
  }
  return true;
}


bool HashTable::linkedListChainDelete(int key, int whichTable) {
  if (linkedListChainSearch(key, whichTable) == NULL) {
    return false;
  }
  node* *table;
  int index;
  if (whichTable == 1) {
    table = table1;
    index = hashFunction1(key);
  }
  else {
    table = table2;
    index = hashFunction2(key);
  }
  node *currentNode = table[index];
  node *previousNode = NULL;
  while (currentNode != NULL) {
    // Found node to be deleted
    if (currentNode->key == key) {
      if (previousNode == NULL) {
        table[index] = currentNode->next;
      }
      else {
        previousNode->next = currentNode->next;
      }
      delete currentNode;
      return true;
    }
    else {
      currentNode = currentNode->next;
    }
  }
}


// Chaining with a Balanced BST


node* HashTable::BSTChainSearch(int key, int whichTable) {
  node* *table;
  int index;
  if (whichTable == 1) {
    table = table1;
    index = hashFunction1(key);
  }
  else {
    table = table2;
    index = hashFunction2(key);
  }
  node* searchNode = table[index];
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


bool HashTable::BSTChainInsert(int key, int whichTable) {
  if (BSTChainSearch(key, whichTable) != NULL) {
    return false;
  }
  node* *table;
  int index;
  if (whichTable == 1) {
    table = table1;
    index = hashFunction1(key);
  }
  else {
    table = table2;
    index = hashFunction2(key);
  }
  if (table[index] == NULL) {
    table[index] = createNode(key, NULL);
    return true;
  }
  node* currentNode = table[index];
  node* previousNode = NULL;
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
    previousNode->right = createNode(key, NULL);
  }
  else if (previousNode->key > key) {
    previousNode->left = createNode(key, NULL);
  }
  return true;
}


bool HashTable::BSTChainDelete(int key, int whichTable) {
  if (BSTChainSearch(key, whichTable) == NULL) {
    return false;
  }
  node* *table;
  int index;
  if (whichTable == 1) {
    table = table1;
    index = hashFunction1(key);
  }
  else {
    table = table2;
    index = hashFunction2(key);
  }
  node* currentNode = table[index];
  node* previousNode = NULL;
  while (currentNode != NULL) {
    // Found the node to be deleted
    if (currentNode->key == key) {
      // Node being deleted is the root of the BST tree
      if (previousNode == NULL) {
        node* searchNode = currentNode;
        // tree only had the one root node
        if (searchNode->left == NULL && searchNode->right == NULL) {
          delete searchNode;
        }
        // make searchNode the minimum value on the right subtree
        else if (searchNode->left == NULL) {
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
        node *searchNode = currentNode->left;
        node *searchNodePrev = NULL;
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
  }
}


// Linear Probing


node* HashTable::linearProbeSearch(int key, int whichTable) {
  node* *table;
  int index;
  if (whichTable == 1) {
    table = table1;
    index = hashFunction1(key);
  }
  else {
    table = table2;
    index = hashFunction2(key);
  }
  node *searchNode = table[index];
  int count = index;
  while (searchNode != NULL && searchNode->key != -1) {
    if (searchNode->key == -1) {
      break;
    }
    if (searchNode->key == key) {
      return searchNode;
    }
    else {
      count++;
      searchNode = table[count];
      if (count == 1019) {
        count = 0;
      }
      if (count == index) {
        return NULL;
      }
    }
  }
  return NULL;
}


bool HashTable::linearProbeInsert(int key, int whichTable) {
  if (linearProbeSearch(key, whichTable) != NULL) {
    return false;
  }
  node* *table;
  int index;
  if (whichTable == 1) {
    table = table1;
    index = hashFunction1(key);
  }
  else {
    table = table2;
    index = hashFunction2(key);
  }
  node *currentNode = table[index];
  int count = index;
  while (currentNode != NULL && currentNode->key != -1) {
    if (currentNode->key == -1) {
      break;
    }
    count++;
    if (count == 1019) {
      count = 0;
    }
    if (count == index) {
      return false;
    }
    currentNode = table[count];
  }
  table[count] = createNode(key, NULL);
  return true;
}


bool HashTable::linearProbeDelete(int key, int whichTable) {
  if (linearProbeSearch(key, whichTable) == NULL) {
    return false;
  }
  node *currentNode = linearProbeSearch(key, whichTable);
  currentNode->key = -1;
  return true;
}


// Cuckoo Hashing


node* HashTable::cuckooHashSearch(int key) {
  int index = hashFunction1(key);
  node *searchNode = table1[index];
  if (searchNode != NULL) {
    if (searchNode->key == key) {
      return searchNode;
    }
    else {
      index = hashFunction2(key);
      searchNode = table2[index];
      if (searchNode != NULL) {
        if (searchNode->key == key) {
          return searchNode;
        }
      }
    }
  }
  return NULL;
}


// Uses recursion to go through each table for a place to put the new node
int HashTable::cuckooHashInsert(int key, int currentTable, int count, int cycle) {
  // Counts the number of times it has cycled through already, if the cycle number is reached, it will assume that there is a cycle and stop
  if (count == cycle) {
    return -1;
  }
  if (cuckooHashSearch(key) != NULL) {
    return 0;
  }
  int index1 = hashFunction1(key);
  int index2 = hashFunction2(key);
  node *currentNode;
  // regular table
  if (currentTable == 0) {
    currentNode = table1[index1];
    if (count == 0) {
      table1[index1] = createNode(key, NULL);
    }
    if (currentNode != NULL && currentNode->key != -1) {
      table1[index1] = cuckooHashSearch(key);
      cuckooHashInsert(currentNode->key, ((currentTable+1)%2), count++, cycle);
    }
  }
  // alt table
  else if (currentTable == 1) {
    currentNode = table2[index2];
    if (count == 0) {
      table2[index2] = createNode(key, NULL);
    }
    if (currentNode != NULL && currentNode->key != -1) {
      table2[index2] = cuckooHashSearch(key);
      cuckooHashInsert(currentNode->key, ((currentTable+1)%2), count++, cycle);
    }
  }
  return 1;
}

bool HashTable::cuckooHashDelete(int key) {
  if (cuckooHashSearch(key) == NULL) {
    return false;
  }
  node *currentNode = cuckooHashSearch(key);
  currentNode->key = -1;
  return true;
}
