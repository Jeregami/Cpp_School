// CPP program to implement hashing with chaining
#include<iostream>
#include "hash.hpp"


using namespace std;

node* HashTable::createNode(int key, node* next)
{
    node* nw = new node;
    nw->key = key;
    nw->next = next;
    return nw;
}

HashTable::HashTable(int bsize)
{
    this->tableSize= bsize;
    table = new node*[tableSize];
    for(int i=0;i<bsize;i++)
        table[i] = nullptr;
}

//function to calculate hash function
unsigned int HashTable::hashFunction(int key)
{
    return (key % tableSize);
}

//function to search
node* HashTable::searchItem(int key) {
    //Compute the index by using the hash function
    int index = hashFunction(key);

    node *searchNode = table[index];

    while (searchNode != NULL) {
        if (searchNode->key == key) {
            return searchNode;
        }
        searchNode = searchNode->next;
    }
    return NULL;
}

//TODO Complete this function
//function to insert
bool HashTable::insertItem(int key) {
    if(!searchItem(key)) {
        int index = hashFunction(key);
        node *newNode = createNode(key, NULL);
        newNode->key = key;
        newNode->next = NULL;
        if (table[index] == NULL) {
            table[index] = newNode;
            return true;
        }
        node *previousNode = NULL;
        node *currentNode = table[index];
        while (currentNode != NULL) {
            if (newNode->key < currentNode->key) {
                if (previousNode == NULL) {
                    newNode->next = currentNode;
                    table[index] = newNode;
                    return true;
                }
                else {
                    previousNode->next = newNode;
                    newNode->next = currentNode;
                }
                break;
            }
            else {
                previousNode = currentNode;
                currentNode = currentNode->next;
            }
        }
        previousNode->next = newNode;
        return true;
    }
    else {
        cout<<"duplicate entry: "<<key<<endl;
        return false;
    }
}

//TODO Complete this function
// function to display hash table
void HashTable::printTable() {
    for (int i = 0; i < tableSize; i++) {
        cout << i << "|| ";
        node *currentNode = table[i];
        while (currentNode != NULL) {
          cout << currentNode->key << " ";
          currentNode = currentNode->next;
        }
        cout << endl;
    }
 }
