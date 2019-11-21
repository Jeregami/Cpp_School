#include "hash.hpp"
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

HashTable::HashTable() {
  table = new node*[tableSize];
  altTable = new node*[tableSize];
  for (int i = 0; i < tableSize; i++) {
    table[i] = nullptr;
    altTable[i] = nullptr;
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

int HashTable::hashFunction(int key) {
  return (key % tableSize);
}

int HashTable::cuckooHashFunction(int key) {
  return floor(key / tableSize);
}

void HashTable::printLLChainTable() {
  for (int i = 0; i < tableSize; i++) {
    node *currentNode = table[i];
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
    node *currentNode = table[i];
    if (currentNode != NULL) {
      node *BSTNode = table[i];
      cout << i << "|| ";
      printTree(BSTNode);
      cout << endl;
    }
  }
}

void HashTable::printLinearTable() {
  for (int i = 0; i < tableSize; i++) {
    node *currentNode = table[i];
    if (currentNode != NULL && currentNode->key != -1) {
      cout << i << "|| " << currentNode->key << endl;
    }
  }
}

void HashTable::printCuckooTable() {
  for (int i = 0; i < tableSize; i++) {
    node *currentNode1 = table[i];
    node *currentNode2 = altTable[i];
    if (currentNode1 != NULL) {
      cout << i << "|| " << currentNode1->key;
      if (currentNode2 != NULL) {
        cout << " " << currentNode2->key;
      }
      cout << endl;
    }
  }
}

// Collision Mechanisms

// Chaining with a Linked List


node* HashTable::linkedListChainSearch(int key) {
  int index = hashFunction(key);
  node* searchNode = table[index];
  while (searchNode != NULL) {
    if (searchNode->key == key) {
      return searchNode;
    }
    searchNode = searchNode->next;
  }
  return NULL;
}


bool HashTable::linkedListChainInsert(int key) {
  if (linkedListChainSearch(key) != NULL) {
    return false;
  }
  int index = hashFunction(key);
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


bool HashTable::linkedListChainDelete(int key) {
  if (linkedListChainSearch(key) == NULL) {
    return false;
  }
  int index = hashFunction(key);
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


node* HashTable::balancedBSTChainSearch(int key) {
  int index = hashFunction(key);
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


bool HashTable::balancedBSTChainInsert(int key) {
  if (balancedBSTChainSearch(key) != NULL) {
    return false;
  }
  int index = hashFunction(key);
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


bool HashTable::balancedBSTChainDelete(int key) {
  if (balancedBSTChainSearch(key) == NULL) {
    return false;
  }
  int index = hashFunction(key);
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


node* HashTable::linearProbeSearch(int key) {
  int index = hashFunction(key);
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


bool HashTable::linearProbeInsert(int key) {
  if (linearProbeSearch(key) != NULL) {
    return false;
  }
  int index = hashFunction(key);
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


bool HashTable::linearProbeDelete(int key) {
  if (linearProbeSearch(key) == NULL) {
    return false;
  }
  int index = hashFunction(key);
  int count = index;
  node *currentNode = table[count];
  while (currentNode != NULL && currentNode->key != -1) {
    currentNode = table[count];
    // Instead of deleting node entirely, node's value is set to -1. Otherwise, the search function might not always work
    if (currentNode->key == key) {
      currentNode->key = -1;
      return true;
    }
    count++;
    if (count == 1019) {
      count = 0;
    }
    if (count == index) {
      return false;
    }
  }
}


// Cuckoo Hashing


node* HashTable::cuckooHashSearch(int key) {
  int index = hashFunction(key);
  node *searchNode = table[index];
  if (searchNode != NULL) {
    if (searchNode->key == key) {
      return searchNode;
    }
    else {
      index = cuckooHashFunction(key);
      searchNode = altTable[index];
      if (searchNode != NULL) {
        if (searchNode->key == key) {
          return searchNode;
        }
      }
    }
  }
  return NULL;
}


// bool HashTable::cuckooHashInsert(int key) {
//   if (cuckooHashSearch(key) != NULL) {
//     return false;
//   }
//   int index1 = hashFunction(key);
//   int index2 = cuckooHashFunction(key);
//   node *currentNode1 = table[index1];
//   node *currentNode2 = altTable[index2];
//   node *tempNode = NULL;
//   while (currentNode1 != NULL) {
//     if (currentNode2 == NULL) {
//       altTable[index2] = createNode(key, NULL);
//       if (tempNode != NULL) {
//         return true;
//       }
//     }
//     else {
//       if (tempNode == NULL) {
//         table[index1] = createNode(key, NULL);
//       }
//       else {
//         table[index1] = tempNode;
//       }
//     }
//     tempNode = currentNode1;
//     index1 = hashFunction(currentNode1->key);
//     index2 = cuckooHashFunction(currentNode2->key);
//     currentNode1 = table[index1];
//     currentNode2 = altTable[index2];
//   }
//   table[index1] = currentNode1;
//   return true;
// }


// bool HashTable::cuckooHashInsert(int key) {
//   if (cuckooHashSearch(key) != NULL) {
//     return false;
//   }
//   int index1 = hashFunction(key);
//   int index2 = cuckooHashFunction(key);
//   node *currentNode = table[index1];
//   node *previousNode = createNode(key, NULL);
//   stack <node*> tableValues;
//   stack <node*> altTableValues;
//   tableValues.push(currentNode);
//   while (true) {
//     if (!tableValues.empty()) {
//       currentNode = tableValues.top();
//       table[index1] = previousNode;
//     }
//     else if (!altTableValues.empty()) {
//       currentNode = altTableValues.top();
//       altTable[index2] = previousNode;
//     }
//     if (currentNode == NULL) {
//       return true;
//     }
//     // Already visited this node, meaning we've created a loop
//     else if (currentNode->visited == true) {
//       return false;
//     }
//     currentNode->visited = true;
//     previousNode = currentNode;
//     index1 = hashFunction(currentNode->key);
//     index2 = cuckooHashFunction(currentNode->key);
//     if (!tableValues.empty()) {
//       tableValues.pop();
//       altTableValues.push(currentNode);
//     }
//     else if (!altTableValues.empty()) {
//       altTableValues.pop();
//       tableValues.push(currentNode);
//     }
//   }
// }

// bool HashTable::cuckooHashInsert(int key) {
//   if (cuckooHashSearch(key) != NULL) {
//     return false;
//   }
//   int index1 = hashFunction(key);
//   int index2 = cuckooHashFunction(key);
//   node *currentNode = table[index1];
//   node *tempNode = createNode(key, NULL);
//   table[index1] = tempNode;
//   while (true) {
//     if (currentNode == NULL) {
//       return true;
//     }
//     tempNode = currentNode;
//     index1 = hashFunction(currentNode->key);
//     index2 = cuckooHashFunction(currentNode->key);
//
//   }
// }


// Uses recursion to go through each table for a place to put the new node
bool HashTable::cuckooHashInsert(int key, int currentTable, int count, int cycle) {
  // Counts the number of times it has cycled through already, if the cycle number is reached, it will assume that there is a cycle and stop
  if (count == cycle) {
    return false;
  }
  if (cuckooHashSearch(key) != NULL) {
    return false;
  }
  int index1 = hashFunction(key);
  int index2 = cuckooHashFunction(key);
  node *currentNode;
  // regular table
  if (currentTable == 0) {
    currentNode = table[index1];
    if (currentNode != NULL) {
      // Special case when on the first cycle
      if (count == 0) {
        table[index1] = createNode(key, NULL);
      }
      else {
        table[index1] = cuckooHashSearch(key);
      }
      cuckooHashInsert(currentNode->key, ((currentTable+1)%2), count++, cycle);
    }
  }
  // alt table
  else if (currentTable == 1) {
    if (currentNode != NULL) {
      currentNode = altTable[index2];
      altTable[index2] = cuckooHashSearch(key);
      cuckooHashInsert(currentNode->key, ((currentTable+1)%2), count++, cycle);
    }
  }
  return true;
}

bool HashTable::cuckooHashDelete(int key) {

}


int main() {
  HashTable table;
  table.cuckooHashInsert(797, 0, 0, 100);
  table.cuckooHashInsert(7930, 0, 0, 100);
  table.cuckooHashInsert(1403, 0, 0, 100);
  table.printCuckooTable();
  table.cuckooHashDelete(797);
  table.printCuckooTable();
}
