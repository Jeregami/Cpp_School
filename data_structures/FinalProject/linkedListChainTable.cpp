#include "linkedListChainTable.hpp"
#include <iostream>
#include <cmath>

using namespace std;

LinkedListChainTable::LinkedListChainTable() {
  tableSize = 10009;
  table = new LLnode*[tableSize];
  for (int i = 0; i < tableSize; i++) {
    table[i] = nullptr;
  }
}

LLnode* LinkedListChainTable::createNode(int key, LLnode* next) {
  LLnode* newNode = new LLnode;
  newNode->key = key;
  newNode->next = next;
  return newNode;
}

int LinkedListChainTable::hashFunction(int key) {
  return (key % tableSize);
}

LLnode* LinkedListChainTable::linkedListChainSearch(int key) {
  int index = hashFunction(key);
  LLnode* searchNode = table[index];
  while (searchNode != NULL) {
    if (searchNode->key == key) {
      return searchNode;
    }
    searchNode = searchNode->next;
  }
  return NULL;
}


bool LinkedListChainTable::linkedListChainInsert(int key) {
  if (linkedListChainSearch(key) != NULL) {
    return false;
  }
  int index = hashFunction(key);
  if (table[index] == NULL) {
      table[index] = createNode(key, NULL);
      return true;
  }
  LLnode* currentNode = table[index];
  LLnode* previousNode = NULL;
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


bool LinkedListChainTable::linkedListChainDelete(int key) {
  if (linkedListChainSearch(key) == NULL) {
    return false;
  }
  int index = hashFunction(key);
  LLnode *currentNode = table[index];
  LLnode *previousNode = NULL;
  while (currentNode != NULL) {
    // Found node to be deleted
    if (currentNode->key == key) {
      if (previousNode == NULL) {
        table[index] = currentNode->next;
      }
      else {
        previousNode->next = currentNode->next;
      }
      currentNode = NULL;
      return true;
    }
    else {
      currentNode = currentNode->next;
    }
  }
}


int LinkedListChainTable::fillTable(vector <int> v, double loadFactor) {
  double numInserted = 0;
  int numDuplicates = 0;
  while ((numInserted / tableSize) < loadFactor) {
    if (linkedListChainInsert(v[numInserted+numDuplicates]) == false) {
      numDuplicates++;
    }
    else {
      numInserted++;
    }
  }
  return numInserted;
}
