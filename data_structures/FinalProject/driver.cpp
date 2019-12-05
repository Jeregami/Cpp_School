#include "linkedListChainTable.cpp"
#include "BSTChainTable.cpp"
#include "linearProbeTable.cpp"
#include "cuckooHashTable.cpp"
#include <ctime>
#include <cmath>
#include <fstream>
#include <sstream>

using namespace std;


// Reads the csv data and returns a vector containing the integers
vector <int> getDataFromCSVFile(string fileName) {
  ifstream file(fileName);
  vector <int> v;
  if (!file.is_open()) {
    cout << "Failed to open file" << endl;
  }
  else {
    string lineData;
    while (getline(file, lineData)) {
      istringstream ss(lineData);
      string number;
      while (getline(ss, number, ',')) {
        v.push_back(stoi(number));
      }
    }
  }
  file.close();
  return v;
}


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
  vector <int> v;
  if (!file.is_open()) {
    cout << "failed to open file" << endl;
  }
  else {
    string line;
    while (getline(file, line)) {
      v.push_back(stoi(line));
    }
    file.close();
  }
  return v;
}


vector <double> linkedListAction(LinkedListChainTable table1, LinkedListChainTable table2, vector <int> v1, vector <int> v2, int function, int numInserted) {
  vector <double> times;
  double execTime;
  int start, stop;
  int num1, num2;
  bool inserted1, inserted2;
  switch (function) {
    // 100 Searches
    case 1:
      for (int i = 0; i < 100; i++) {
        num1 = v1[rand() % numInserted];
        num2 = v2[rand() % numInserted];
        start = clock();
        table1.linkedListChainSearch(num1);
        table2.linkedListChainSearch(num2);
        stop = clock();
        execTime = (double)(stop-start)/CLOCKS_PER_SEC;
        times.push_back(execTime);
      }
      cout << "100 Searches";
      break;
    // 100 Inserts
    case 2:
      for (int i = 0; i < 100; i++) {
        // Random values used for testing
        // num1 = rand() % 200180;
        // num2 = rand() % 200180;
        num1 = v1[numInserted+i];
        num2 = v2[numInserted+i];
        start = clock();
        inserted1 = table1.linkedListChainInsert(num1);
        inserted2 = table2.linkedListChainInsert(num2);
        stop = clock();
        execTime = (double)(stop-start)/CLOCKS_PER_SEC;
        times.push_back(execTime);
        // Removes integers that were just added to table to keep load factor same if the integer was successfully added
        if (inserted1 == true) {
          table1.linkedListChainDelete(num1);
        }
        if (inserted2 == true) {
          table2.linkedListChainDelete(num2);
        }
      }
      cout << "100 Inserts";
      break;
    // 100 Deletes
    case 3:
      for (int i = 0; i < 100; i++) {
        num1 = v1[rand() % numInserted];
        num2 = v2[rand() % numInserted];
        start = clock();
        table1.linkedListChainDelete(num1);
        table2.linkedListChainDelete(num2);
        stop = clock();
        execTime = (double)(stop-start)/CLOCKS_PER_SEC;
        times.push_back(execTime);
        // Adds integers that were deleted back to table to keep load factor same
        table1.linkedListChainInsert(num1);
        table2.linkedListChainInsert(num2);
      }
      cout << "100 Deletes";
      break;
  }
  return times;
}


vector <double> BSTAction(BSTChainTable table1, BSTChainTable table2, vector <int> v1, vector <int> v2, int function, int numInserted) {
  vector <double> times;
  double execTime;
  int start, stop;
  int num1, num2;
  bool inserted1, inserted2;
  switch (function) {
    // 100 Searches
    case 1:
      for (int i = 0; i < 100; i++) {
        num1 = v1[rand() % numInserted];
        num2 = v2[rand() % numInserted];
        start = clock();
        table1.BSTChainSearch(num1);
        table2.BSTChainSearch(num2);
        stop = clock();
        execTime = (double)(stop-start)/CLOCKS_PER_SEC;
        times.push_back(execTime);
      }
      cout << "100 Searches";
      break;
      // 100 Inserts
      case 2:
        for (int i = 0; i < 100; i++) {
          // Random values used for testing
          // num1 = rand() % 200180;
          // num2 = rand() % 200180;
          num1 = v1[numInserted+i];
          num2 = v2[numInserted+i];
          start = clock();
          inserted1 = table1.BSTChainInsert(num1);
          inserted2 = table2.BSTChainInsert(num2);
          stop = clock();
          execTime = (double)(stop-start)/CLOCKS_PER_SEC;
          times.push_back(execTime);
          // Removes integers that were just added to table to keep load factor same if the integer was successfully added
          if (inserted1 == true) {
            table1.BSTChainDelete(num1);
          }
          if (inserted2 == true) {
            table2.BSTChainDelete(num2);
          }
        }
        cout << "100 Inserts";
        break;
      // 100 Deletes
      case 3:
        for (int i = 0; i < 100; i++) {
          // num1 = v1[rand() % numInserted];
          // num2 = v2[rand() % numInserted];
          num1 = v1[rand() % numInserted];
          num2 = v2[rand() % numInserted];
          start = clock();
          table1.BSTChainDelete(num1);
          table2.BSTChainDelete(num2);
          stop = clock();
          execTime = (double)(stop-start)/CLOCKS_PER_SEC;
          times.push_back(execTime);
          // Adds integers that were deleted back to table to keep load factor same
          table1.BSTChainInsert(num1);
          table2.BSTChainInsert(num2);
        }
        cout << "100 Deletes";
        break;
  }
  return times;
}


vector <double> linearAction(LinearProbeTable table1, LinearProbeTable table2, vector <int> v1, vector <int> v2, int function, int numInserted) {
  vector <double> times;
  double execTime;
  int start, stop;
  int num1, num2;
  bool inserted1, inserted2;
  switch (function) {
    // 100 Searches
    case 1:
      for (int i = 0; i < 100; i++) {
        num1 = v1[rand() % numInserted];
        num2 = v2[rand() % numInserted];
        start = clock();
        table1.linearProbeSearch(num1);
        table2.linearProbeSearch(num2);
        stop = clock();
        execTime = (double)(stop-start)/CLOCKS_PER_SEC;
        times.push_back(execTime);
      }
      cout << "100 Searches";
      break;
      // 100 Inserts
      case 2:
        for (int i = 0; i < 100; i++) {
          // Random values used for testing
          // num1 = rand() % 200180;
          // num2 = rand() % 200180;
          num1 = v1[numInserted+i];
          num2 = v2[numInserted+i];
          start = clock();
          inserted1 = table1.linearProbeInsert(num1);
          inserted2 = table2.linearProbeInsert(num2);
          stop = clock();
          execTime = (double)(stop-start)/CLOCKS_PER_SEC;
          times.push_back(execTime);
          // Removes integers that were just added to table to keep load factor same if the integer was successfully added
          if (inserted1 == true) {
            table1.linearProbeDelete(num1);
          }
          if (inserted2 == true) {
            table2.linearProbeDelete(num2);
          }
        }
        cout << "100 Inserts";
        break;
      // 100 Deletes
      case 3:
        for (int i = 0; i < 100; i++) {
          num1 = v1[rand() % numInserted];
          num2 = v2[rand() % numInserted];
          start = clock();
          table1.linearProbeDelete(num1);
          table2.linearProbeDelete(num2);
          stop = clock();
          execTime = (double)(stop-start)/CLOCKS_PER_SEC;
          times.push_back(execTime);
          // Adds integers that were deleted back to table to keep load factor same
          table1.linearProbeInsert(num1);
          table2.linearProbeInsert(num2);
        }
        cout << "100 Deletes";
        break;
  }
  return times;
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

// Finds the smallest prime number that's greater than the given number
int findNextPrimeNum(int num) {
  int nextPrime = num;
  bool found = false;
  while (found == false) {
    nextPrime++;
    found = isPrime(nextPrime);
  }
  return nextPrime;
}

CuckooHashTable rebuildCuckooHashTable(CuckooHashTable table, vector <int> v, int numInserted, int tableSize) {
  CuckooHashTable newTable(findNextPrimeNum(tableSize));
  for (int i = 0; i < numInserted; i++) {
    newTable.cuckooHashInsert(v[i], 0, 0, 10000);
  }
  return newTable;
}


vector <double> cuckooAction(CuckooHashTable table, vector <int> v, int function, int numInserted, int tableSize, double loadFactor, int *cycles) {
  double execTime;
  vector <double> times;
  int start, stop;
  int num;
  bool cycle = false;
  int inserted;
  switch (function) {
    // 100 Searches
    case 1:
      for (int i = 0; i < 100; i++) {
        num = v[rand() % numInserted];
        start = clock();
        table.cuckooHashSearch(num);
        stop = clock();
        execTime = (double)(stop-start)/CLOCKS_PER_SEC;
        times.push_back(execTime);
      }
      cout << "100 Searches";
      break;
    // 100 Inserts
    case 2:
      for (int i = 0; i < 100; i++) {
        // Random values used for testing
        // num = v[rand() % 200180];
        num = v[numInserted+i];
        start = clock();
        inserted = table.cuckooHashInsert(num, 0, 0, 10000);
        stop = clock();
        if (inserted == -1) {
          cycle = true;
        }
        else if (inserted == 1) {
          table.cuckooHashDelete(num);
        }
        execTime = (double)(stop-start)/CLOCKS_PER_SEC;
        times.push_back(execTime);
      }
      // If a cycle was present, it will rebuild the hash table and with new table size and hash functions
      if (cycle == true) {
        cout << "Failed to Insert One or More Values into Hash Table. Rebuilding..." << endl;
        cycles++;
        CuckooHashTable newTable = rebuildCuckooHashTable(table, v, numInserted, tableSize);
        cuckooAction(newTable, v, function, numInserted, tableSize, loadFactor, cycles);
      }
      else {
        cout << "100 Inserts";
      }
      break;
    // 100 Deletes
    case 3:
      for (int i = 0; i < 100; i++) {
        num = v[rand() % numInserted];
        start = clock();
        table.cuckooHashDelete(num);
        stop = clock();
        execTime = (double)(stop-start)/CLOCKS_PER_SEC;
        times.push_back(execTime);
        table.cuckooHashInsert(num, 0, 0, 10000);
      }
      cout << "100 Deletes";
      break;
  }
  return times;
}


double getAvgTime(vector <double> times) {
  double avgTime = 0;
  for (int i = 0; i < times.size(); i++) {
    avgTime += times[i];
  }
  return avgTime / times.size();
}


double getStdDev(vector <double> times) {
  double avgTime = getAvgTime(times);
  double stdDev = 0;
  double variance;
  for (int i = 0; i < times.size(); i++) {
    variance = pow(avgTime-times[i], 2);
    stdDev += variance;
  }
  return sqrt(stdDev);
}

  /* argc 1: Hash table type
   * 1. Chaining with a Linked List
   * 2. Chaining with a BST
   * 3. Linear Probing
   * 4. Cuckoo Hashing
   *
   * argc 2: Function to be done
   * 1. 100 Searches
   * 2. 100 Inserts
   * 3. 100 Deletes
   *
   * argc 3: Load Factor
   */
int main(int argc, char const *argv[]) {
  if (argc != 4) {
    cout << "Incorrect usage." << endl;
    return -1;
  }
  // These functions were for help testing. They filled the file with random integers and then created vectors containing those integers
  // addRandomIntegersToFile("randomIntegers1.csv", 10009);
  // addRandomIntegersToFile("randomIntegers2.csv", 10009);
  // vector <int> v1 = getRandomIntegersFromFile("randomIntegers1.csv");
  // vector <int> v2 = getRandomIntegersFromFile("randomIntegers2.csv");

  srand(time(NULL));

  // These vectors contain the data from the csv files that were given to us
  vector <int> v1 = getDataFromCSVFile("dataSetA.csv");
  vector <int> v2 = getDataFromCSVFile("dataSetB.csv");

  int tableType = stoi(argv[1]);
  int function  = stoi(argv[2]);
  double loadFactor= stod(argv[3]);

  double numInserted = 0;
  vector <double> times;
  double avgTime;
  double stdDev;


  // Linked List Chaining
  if (tableType == 1) {
    LinkedListChainTable LLTable1;
    LinkedListChainTable LLTable2;
    numInserted = LLTable1.fillTable(v1, loadFactor);
    LLTable2.fillTable(v2, loadFactor);
    times = linkedListAction(LLTable1, LLTable2, v1, v2, function, numInserted);
    cout << " Using Linked List Chaining" << endl;
  }

  // BST Chaining
  else if (tableType == 2) {
    BSTChainTable BSTTable1;
    BSTChainTable BSTTable2;
    numInserted = BSTTable1.fillTable(v1, loadFactor);
    BSTTable2.fillTable(v2, loadFactor);
    times = BSTAction(BSTTable1, BSTTable2, v1, v2, function, numInserted);
    cout << " Using BST chaining" << endl;
  }

  // Linear Probing
  else if (tableType == 3) {
    LinearProbeTable linearTable1;
    LinearProbeTable linearTable2;
    numInserted = linearTable1.fillTable(v1, loadFactor);
    linearTable2.fillTable(v2, loadFactor);
    times = linearAction(linearTable1, linearTable2, v1, v2, function, numInserted);
    cout << " Using linear probing" << endl;
  }

  // Cuckoo Hashing
  else if (tableType == 4) {
    CuckooHashTable cuckooTable;
    int tableSize = cuckooTable.getTableSize();
    int *cycles = 0;
    double currentLoadFactor = (double)(numInserted / tableSize);
    // While loop created to ensure that if a cycle is found while filling the table, it will rebuild itself until there is no more cycle
    while (currentLoadFactor < loadFactor) {
      numInserted = cuckooTable.fillTable(v1, loadFactor);
      currentLoadFactor = (double)(numInserted / tableSize);
      if (currentLoadFactor < loadFactor) {
        cycles++;
        cuckooTable = rebuildCuckooHashTable(cuckooTable, v1, numInserted, tableSize);
      }
    }
    // A cycle occurred and the hash table needs to be rebuilt
    times = cuckooAction(cuckooTable, v1, function, numInserted, cuckooTable.getTableSize(), loadFactor, cycles);
    if (tableType == 4 && function == 2) {
      if (cycles > 0) {
        cout << "Rebuilt the hash table " << cycles << "times." << endl;
      }
    }
    cout << " Using cuckoo hashing" << endl;
  }

  avgTime = getAvgTime(times);
  stdDev = getStdDev(times);

  cout << "Average execution time: " << avgTime << endl;
  cout << "Standard Deviation: " << stdDev << endl;
}
