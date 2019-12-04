#include "linearProbeTable.hpp"
#include <iostream>
#include <cmath>

using namespace std;

LinearProbeTable::LinearProbeTable() {
  tableSize = 10009;
  table = new linearNode*[tableSize];
  for (int i = 0; i < tableSize; i++) {
    table[i] = nullptr;
  }
}

linearNode* LinearProbeTable::createNode(int key) {
  linearNode* newNode = new linearNode;
  newNode->key = key;
  return newNode;
}

int LinearProbeTable::hashFunction(int key) {
  return (key % tableSize);
}

linearNode* LinearProbeTable::linearProbeSearch(int key) {
  int index = hashFunction(key);
  linearNode *searchNode = table[index];
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
      if (count == tableSize) {
        count = 0;
      }
      if (count == index) {
        return NULL;
      }
    }
  }
  return NULL;
}


bool LinearProbeTable::linearProbeInsert(int key) {
  if (linearProbeSearch(key) != NULL) {
    return false;
  }
  int index = hashFunction(key);
  linearNode *currentNode = table[index];
  int count = index;
  while (currentNode != NULL && currentNode->key != -1) {
    if (currentNode->key == -1) {
      break;
    }
    count++;
    if (count == tableSize) {
      count = 0;
    }
    if (count == index) {
      return false;
    }
    currentNode = table[count];
  }
  table[count] = createNode(key);
  return true;
}


bool LinearProbeTable::linearProbeDelete(int key) {
  if (linearProbeSearch(key) == NULL) {
    return false;
  }
  linearNode *currentNode = linearProbeSearch(key);
  // Value is set to -1 instead of just being deleted. Otherwise, linearProbeSearch has a chance to not find a value that exists in table
  currentNode->key = -1;
  return true;
}


int LinearProbeTable::fillTable(vector <int> v, double loadFactor) {
  double numInserted = 0;
  int numDuplicates = 0;
  while ((numInserted / tableSize) < loadFactor) {
    if (linearProbeInsert(v[numInserted+numDuplicates]) == false) {
      numDuplicates++;
    }
    else {
      numInserted++;
    }
  }
  return numInserted;
}
