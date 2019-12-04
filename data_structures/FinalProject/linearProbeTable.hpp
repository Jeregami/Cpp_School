#include <string>

using namespace std;

struct linearNode {
    int key;
};

class LinearProbeTable {
  int tableSize;
  linearNode* *table;
  linearNode* createNode(int key);
public:
  LinearProbeTable();
  int hashFunction(int key);
  linearNode* linearProbeSearch(int key);
  bool linearProbeInsert(int key);
  bool linearProbeDelete(int key);
  int fillTable(vector <int> v, double loadFactor);
};
