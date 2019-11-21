#include <string>

using namespace std;

struct node {
    int key;
    struct node* next;
    struct node* left;
    struct node* right;
};

class HashTable {
    int tableSize = 1019;
    node* *table;
    node* *altTable;
    node* createNode(int key, node* next);
public:
    HashTable();
    int hashFunction(int key);
    int cuckooHashFunction(int key);
    void printLLChainTable();
    void printBSTChainTable();
    void printLinearTable();
    void printCuckooTable();
    // Collision Resolution Mechanisms

    // Chaining with a Linked List
    node* linkedListChainSearch(int key);
    bool linkedListChainInsert(int key);
    bool linkedListChainDelete(int key);

    // Chaining with a Balanced BST
    node* balancedBSTChainSearch(int key);
    bool balancedBSTChainInsert(int key);
    bool balancedBSTChainDelete(int key);

    // Linear Probing
    node* linearProbeSearch(int key);
    bool linearProbeInsert(int key);
    bool linearProbeDelete(int key);

    // Cuckoo Hashing
    node* cuckooHashSearch(int key);
    bool cuckooHashInsert(int key, int currentTable, int count, int cycle);
    bool cuckooHashDelete(int key);
};
