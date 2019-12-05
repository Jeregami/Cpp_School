#include <string>

using namespace std;

struct cuckooNode {
    int key;
};

class CuckooHashTable {
  int tableSize;
  cuckooNode* *table1;
  cuckooNode* *table2;
  cuckooNode* createNode(int key);
public:
  CuckooHashTable();
  CuckooHashTable(int newTableSize);
  int getTableSize();
  int hashFunction1(int key);
  int hashFunction2(int key);
  cuckooNode* cuckooHashSearch(int key);
  int cuckooHashInsert(int key, int count, int cycle);
  bool cuckooHashDelete(int key);
  int fillTable(vector <int> v, double loadFactor);
};
