#include <string>

using namespace std;

struct node {
    int key;
    struct node* next;
    struct node* left;
    struct node* right;
};

class HashTable {
    int tableSize;
    node* *table1;
    node* *table2;
    node* createNode(int key, node* next);
public:
    HashTable();
    HashTable(int newTableSize);
    int hashFunction1(int key);
    int hashFunction2(int key);
    void printLLChainTable();
    void printBSTChainTable();
    void printLinearTable();
    void printCuckooTable();
    // Collision Resolution Mechanisms

    // Chaining with a Linked List
    node* linkedListChainSearch(int key, int whichTable);
    bool linkedListChainInsert(int key, int whichTable);
    bool linkedListChainDelete(int key, int whichTable);

    // Chaining with a Balanced BST
    node* BSTChainSearch(int key, int whichTable);
    bool BSTChainInsert(int key, int whichTable);
    bool BSTChainDelete(int key, int whichTable);

    // Linear Probing
    node* linearProbeSearch(int key, int whichTable);
    bool linearProbeInsert(int key, int whichTable);
    bool linearProbeDelete(int key, int whichTable);

    // Cuckoo Hashing
    node* cuckooHashSearch(int key);
    int cuckooHashInsert(int key, int currentTable, int count, int cycle);
    bool cuckooHashDelete(int key);
};
