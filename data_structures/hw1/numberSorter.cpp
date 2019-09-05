#include <iostream>
#include <fstream>

using namespace std;

// myArray[100]: sorted integer array
// numEntries: number of elements inserted so far
// newValue: incoming value to be sorted into the array
int insertIntoSortedArray(int myArray[100], int numEntries, int newValue) {
  if (numEntries == 0) {
    myArray[0] = newValue;
    numEntries++;
    return numEntries;
  }
  for (int i = numEntries; i >= 0; i--) {
    if (newValue >= myArray[i-1] || i == 0) {
      for (int j = numEntries; j > i; j--) {
        myArray[j] = myArray[j-1];
      }
      myArray[i] = newValue;
      numEntries++;
      return numEntries;
    }
  }
}

// Arguments: Input File
int main(int argc, char *argv[]) {
  ifstream file(argv[1]);
  if (!file.is_open()) {
    cout << "Failed to open the file" << endl;
  }
  int myArray[100];
  string line;
  int numValues = 0;
  while (getline(file,line)) {
    insertIntoSortedArray(myArray, numValues, stoi(line));
    numValues++;
    for (int i = 0; i < numValues; i++) {
      cout << myArray[i];
      if (i+1 != numValues) {
        cout << ", ";
      }
    }
    cout << endl;
  }
  file.close();
}
