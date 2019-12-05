#include "cuckooHashTable.hpp"
#include <iostream>
#include <cmath>

using namespace std;

CuckooHashTable::CuckooHashTable() {
  tableSize = 10009;
  table1 = new cuckooNode*[tableSize];
  table2 = new cuckooNode*[tableSize];
  for (int i = 0; i < tableSize; i++) {
    table1[i] = nullptr;
    table2[i] = nullptr;
  }
}

CuckooHashTable::CuckooHashTable(int newTableSize) {
  tableSize = newTableSize;
  table1 = new cuckooNode*[tableSize];
  table2 = new cuckooNode*[tableSize];
  for (int i = 0; i < tableSize; i++) {
    table1[i] = nullptr;
    table2[i] = nullptr;
  }
}

cuckooNode* CuckooHashTable::createNode(int key) {
  cuckooNode* newNode = new cuckooNode;
  newNode->key = key;
  return newNode;
}

int CuckooHashTable::getTableSize() {
  return tableSize;
}

int CuckooHashTable::hashFunction1(int key) {
  return (key % tableSize);
}

int CuckooHashTable::hashFunction2(int key) {
  return floor(key / tableSize);
}

cuckooNode* CuckooHashTable::cuckooHashSearch(int key) {
  int index = hashFunction1(key);
  cuckooNode *searchNode = table1[index];
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
int CuckooHashTable::cuckooHashInsert(int key, int count, int cycle) {
  // Counts the number of times it has cycled through already, if the cycle number is reached, it will assume that there is a cycle and stop
  if (count == cycle) {
    return -1;
  }
  if (cuckooHashSearch(key) != NULL) {
    return 0;
  }
  int currentTable = count % 2;
  int index1 = hashFunction1(key);
  int index2 = hashFunction2(key);
  cuckooNode *currentNode;
  // regular table
  if (currentTable == 0) {
    currentNode = table1[index1];
    table1[index1] = createNode(key);
    if (currentNode != NULL && currentNode->key != -1) {
      cuckooHashInsert(currentNode->key, count+1, cycle);
    }
  }
  // alt table
  else if (currentTable == 1) {
    currentNode = table2[index2];
    table2[index2] = createNode(key);
    if (currentNode != NULL && currentNode->key != -1) {
      cuckooHashInsert(currentNode->key, count+1, cycle);
    }
  }
  return 1;
}

bool CuckooHashTable::cuckooHashDelete(int key) {
  if (cuckooHashSearch(key) == NULL) {
    return false;
  }
  cuckooNode *currentNode = cuckooHashSearch(key);
  currentNode->key = -1;
  return true;
}


int CuckooHashTable::fillTable(vector <int> v, double loadFactor) {
  double numInserted = 0;
  int numDuplicates = 0;
  int cycleTracker;
  while ((numInserted / tableSize) < loadFactor) {
    cycleTracker = cuckooHashInsert(v[numInserted+numDuplicates], 0, 500);
    if (cycleTracker == 0) {
      numDuplicates++;
    }
    // If a cycle is detected, it will return 0 so the table can be rebuilt
    else if (cycleTracker == -1) {
      return numInserted;
    }
    else {
      numInserted++;
    }
  }
  return numInserted;
}
