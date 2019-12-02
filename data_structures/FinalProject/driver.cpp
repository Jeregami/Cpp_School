#include "hash.cpp"
#include <ctime>
#include <fstream>

using namespace std;

// Adds an amount of random integers to a file
void addRandomIntegersToFile(string fileName, int numAdding) {
  srand(time(NULL));
  ofstream file(fileName);
  if (!file.is_open()) {
    cout << "failed to open file" << endl;
    return;
  }
  int randomInt;
  for (int i = 0; i < numAdding; i++) {
    randomInt = (rand() % 200180);
    file << randomInt << endl;
  }
  file.close();
}

// Puts the random integers obtained from a file into a vector of integers
vector <int> getRandomIntegersFromFile(string fileName) {
  ifstream file(fileName);
  if (!file.is_open()) {
    cout << "failed to open file" << endl;
  }
  vector <int> v;
  string line;
  while (getline(file, line)) {
    v.push_back(stoi(line));
  }
  file.close();
  return v;
}

/* Fills the hash table with values until it reaches the specified load factor
 * hashTableType:
 * 1 = Chaining with a Linked List
 * 2 = Chaining with a BST
 * 3 = Linear Probing
 * 4 = Cuckoo Hashing
 */
 // Returns number of integers put into the hash table
int fillTable(HashTable table, vector <int> randomIntegers1, vector <int> randomIntegers2, int hashTableType, double loadFactor) {

  double numInserted = 0;
  switch (hashTableType) {
    case 1:
      while ((numInserted / 10009) < loadFactor) {
        table.linkedListChainInsert(randomIntegers1[numInserted], 1);
        table.linkedListChainInsert(randomIntegers2[numInserted], 2);
        numInserted++;
      }
      return numInserted;
    case 2:
      while ((numInserted / 10009) < loadFactor) {
        table.BSTChainInsert(randomIntegers1[numInserted], 1);
        table.BSTChainInsert(randomIntegers2[numInserted], 2);
        numInserted++;
      }
      return numInserted;
    case 3:
      while (numInserted / 10009 < loadFactor) {
        table.linearProbeInsert(randomIntegers1[numInserted], 1);
        table.linearProbeInsert(randomIntegers2[numInserted], 2);
        numInserted++;
      }
      break;
    case 4:
      int cycleTracker;
      while (numInserted / 10009 < loadFactor) {
        cycleTracker = table.cuckooHashInsert(randomIntegers1[numInserted], 0, 0, 500);
        if (cycleTracker == -1) {
          cout << "Failed to insert into hash table. Increase size of hash table" << endl;
          return numInserted;
        }
        numInserted++;
      }
      break;
  }
}


double linkedListAction(HashTable table, vector <int> v1, vector <int> v2, int function, int loadFactor, int numInserted) {
  double execTime;
  double avgTime = 0;
  int start, stop;
  int num1;
  int num2;
  switch (function) {
    // 100 Searches
    case 1:
      for (int i = 0; i < 100; i++) {
        num1 = v1[rand() % numInserted];
        num2 = v2[rand() % numInserted];
        start = clock();
        table.linkedListChainSearch(num1, 1);
        table.linkedListChainSearch(num2, 2);
        stop = clock();
        execTime = (double)(stop-start)/CLOCKS_PER_SEC;
        avgTime += execTime;
      }
      break;
    // 100 Inserts
    case 2:
      for (int i = 0; i < 100; i++) {
        num1 = rand() % 200180;
        num2 = rand() % 200180;
        start = clock();
        table.linkedListChainInsert(num1, 1);
        table.linkedListChainInsert(num2, 2);
        stop = clock();
        execTime = (double)(stop-start)/CLOCKS_PER_SEC;
        avgTime += execTime;
        table.linkedListChainDelete(num1, 1);
        table.linkedListChainDelete(num2, 2);
      }
      break;
    // 100 Deletes
    case 3:
      for (int i = 0; i < 100; i++) {
        num1 = v1[rand() % numInserted];
        num2 = v2[rand() % numInserted];
        start = clock();
        table.linkedListChainDelete(num1, 1);
        table.linkedListChainDelete(num2, 2);
        stop = clock();
        execTime = (double)(stop-start)/CLOCKS_PER_SEC;
        avgTime += execTime;
        table.linkedListChainInsert(num1, 1);
        table.linkedListChainInsert(num2, 2);
      }
      break;
  }
  return avgTime = avgTime / 100;
}


double BSTAction(HashTable table, vector <int> v1, vector <int> v2, int function, int loadFactor, int numInserted) {
  double execTime;
  double avgTime = 0;
  int start, stop;
  int num1;
  int num2;
  switch (function) {
    // 100 Searches
    case 1:
      for (int i = 0; i < 100; i++) {
        num1 = v1[rand() % numInserted];
        num2 = v2[rand() % numInserted];
        start = clock();
        table.BSTChainSearch(num1, 1);
        table.BSTChainSearch(num2, 2);
        stop = clock();
        execTime = (double)(stop-start)/CLOCKS_PER_SEC;
        avgTime += execTime;
      }
      break;
      // 100 Inserts
      case 2:
        for (int i = 0; i < 100; i++) {
          num1 = rand() % 200180;
          num2 = rand() % 200180;
          start = clock();
          table.BSTChainInsert(num1, 1);
          table.BSTChainInsert(num2, 2);
          stop = clock();
          execTime = (double)(stop-start)/CLOCKS_PER_SEC;
          avgTime += execTime;
          table.BSTChainDelete(num1, 1);
          table.BSTChainDelete(num2, 2);
        }
        break;
      // 100 Deletes
      case 3:
        for (int i = 0; i < 100; i++) {
          num1 = v1[rand() % numInserted];
          num2 = v2[rand() % numInserted];
          start = clock();
          table.BSTChainDelete(num1, 1);
          table.BSTChainDelete(num2, 2);
          stop = clock();
          execTime = (double)(stop-start)/CLOCKS_PER_SEC;
          avgTime += execTime;
          table.BSTChainInsert(num1, 1);
          table.BSTChainInsert(num2, 2);
        }
        break;
  }
  return avgTime = avgTime / 100;
}


double linearAction(HashTable table, vector <int> v1, vector <int> v2, int function, int loadFactor, int numInserted) {
  double execTime;
  double avgTime = 0;
  int start, stop;
  int num1;
  int num2;
  switch (function) {
    // 100 Searches
    case 1:
      for (int i = 0; i < 100; i++) {
        num1 = v1[rand() % numInserted];
        num2 = v2[rand() % numInserted];
        start = clock();
        table.linearProbeSearch(num1, 1);
        table.linearProbeSearch(num2, 2);
        stop = clock();
        execTime = (double)(stop-start)/CLOCKS_PER_SEC;
        avgTime += execTime;
      }
      break;
      // 100 Inserts
      case 2:
        for (int i = 0; i < 100; i++) {
          num1 = rand() % 200180;
          num2 = rand() % 200180;
          start = clock();
          table.linearProbeInsert(num1, 1);
          table.linearProbeInsert(num2, 2);
          stop = clock();
          execTime = (double)(stop-start)/CLOCKS_PER_SEC;
          avgTime += execTime;
          table.linearProbeDelete(num1, 1);
          table.linearProbeDelete(num2, 2);
        }
        break;
      // 100 Deletes
      case 3:
        for (int i = 0; i < 100; i++) {
          num1 = v1[rand() % numInserted];
          num2 = v2[rand() % numInserted];
          start = clock();
          table.linearProbeDelete(num1, 1);
          table.linearProbeDelete(num2, 2);
          stop = clock();
          execTime = (double)(stop-start)/CLOCKS_PER_SEC;
          avgTime += execTime;
          table.linearProbeInsert(num1, 1);
          table.linearProbeInsert(num2, 2);
        }
        break;
  }
  return avgTime = avgTime / 100;
}

// Returns true if given number is prime, false if not prime
bool isPrime(int num) {
  for (int i = 2; i < num/2; i++) {
    if (num % i == 0) {
      return false;
    }
  }
  return true;
}

int findNextPrimeNum(int num) {
  int nextPrime = num;
  bool found = false;
  while (found == false) {
    nextPrime++;
    found = isPrime(nextPrime);
  }
  return nextPrime;
}

HashTable rebuildCuckooHashTable(HashTable table, vector <int> v1, int numInserted, int tableSize) {
  HashTable newTable(findNextPrimeNum(tableSize));
  for (int i = 0; i < numInserted; i++) {
    newTable.cuckooHashInsert(v1[i], 0, 0, 10000);
  }
  return newTable;
}


double cuckooAction(HashTable table, vector <int> v1, int function, int loadFactor, int numInserted, int tableSize, int *cycles) {
  double execTime;
  double avgTime = 0;
  int start, stop;
  int num;
  bool cycle = false;
  switch (function) {
    // 100 Searches
    case 1:
    for (int i = 0; i < 100; i++) {
      num = v1[rand() % numInserted];
      start = clock();
      table.cuckooHashSearch(num);
      stop = clock();
      execTime = (double)(stop-start)/CLOCKS_PER_SEC;
      avgTime += execTime;
    }
      break;
    // 100 Inserts
    case 2:
      for (int i = 0; i < 100; i++) {
        num = v1[rand() % 200180];
        start = clock();
        if (table.cuckooHashInsert(num, 0, 0, 10000) == -1) {
          cycle = true;
        }
        stop = clock();
        execTime = (double)(stop-start)/CLOCKS_PER_SEC;
        avgTime += execTime;
      }
      // If a cycle was present, it will rebuild the hash table and with new table size and hash functions
      if (cycle == true) {
        cout << "Failed to Insert One or More Values into Hash Table. Rebuilding..." << endl;
        cycles++;
        HashTable newTable = rebuildCuckooHashTable(table, v1, numInserted, tableSize);
        cuckooAction(newTable, v1, function, loadFactor, numInserted, tableSize, cycles);
      }
      break;
    // 100 Deletes
    case 3:
    for (int i = 0; i < 100; i++) {
      num = v1[rand() % numInserted];
      start = clock();
      table.cuckooHashDelete(num);
      stop = clock();
      execTime = (double)(stop-start)/CLOCKS_PER_SEC;
      avgTime += execTime;
      table.cuckooHashInsert(num, 0, 0, 10000);
    }
      break;
  }
  return avgTime = avgTime / 100;
}


  /* argc 1: Hash table type
   * 1. Chaining with a Linked List
   * 2. Chaining with a BST
   * 3. Linear Probing
   * 4. Cuckoo Hashing
   *
   * argc 2: Load Factor
   * argc 3: Function to be done
   * 1. 100 Searches
   * 2. 100 Inserts
   * 3. 100 Deletes
   */
int main(int argc, char const *argv[]) {
  if (argc != 4) {
    cout << "Incorrect usage." << endl;
    return -1;
  }
  HashTable table;
  addRandomIntegersToFile("randomIntegers1.csv", 10009);
  addRandomIntegersToFile("randomIntegers2.csv", 10009);
  vector <int> v1 = getRandomIntegersFromFile("randomIntegers1.csv");
  vector <int> v2 = getRandomIntegersFromFile("randomIntegers2.csv");

  int tableType = stoi(argv[1]);
  double loadFactor = stod(argv[2]);
  int function = stoi(argv[3]);

  int numInserted = fillTable(table, v1, v2, tableType, loadFactor);
  int *cycles = 0;
  double avgTime;

  switch (tableType) {
    case 1:
      avgTime = linkedListAction(table, v1, v2, function, loadFactor, numInserted);
      break;
    case 2:
      avgTime = BSTAction(table, v1, v2, function, loadFactor, numInserted);
      break;
    case 3:
      avgTime = linearAction(table, v1, v2, function, loadFactor, numInserted);
      break;
    case 4:
      avgTime = cuckooAction(table, v1, function, loadFactor, numInserted, 10009, cycles);
      break;
  }
  if (tableType == 4 && function == 2) {
    if (cycles > 0) {
      cout << "Rebuilt the hash table " << cycles << "times." << endl;
    }
  }
  cout << "Average execution time: " << avgTime << endl;
}
