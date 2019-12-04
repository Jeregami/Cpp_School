#include <string>
#include <vector>

using namespace std;

struct LLnode {
    int key;
    struct LLnode* next;
};

class LinkedListChainTable {
  int tableSize;
  LLnode* *table;
  LLnode* createNode(int key, LLnode* next);
public:
  LinkedListChainTable();
  int hashFunction(int key);
  LLnode* linkedListChainSearch(int key);
  bool linkedListChainInsert(int key);
  bool linkedListChainDelete(int key);
  int fillTable(vector <int> v, double loadFactor);
};
