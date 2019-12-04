#include <string>

using namespace std;

struct BSTNode {
    int key;
    struct BSTNode* left;
    struct BSTNode* right;
};

class BSTChainTable {
  int tableSize;
  BSTNode* *table;
  BSTNode* createNode(int key);
public:
  BSTChainTable();
  int hashFunction(int key);
  BSTNode* BSTChainSearch(int key);
  bool BSTChainInsert(int key);
  bool BSTChainDelete(int key);
  int fillTable(vector <int> v, double loadFactor);
};
