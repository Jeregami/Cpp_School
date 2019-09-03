#include <iostream>
#include <fstream>

using namespace std;

// myArray[100]: sorted integer array
// numEntries: number of elements inserted so far
// newValue: incoming value to be sorted into the array
int insertIntoSortedArray(int myArray[100], int numEntries, int newValue) {
  if (numEntries < 2) {
    if (numEntries == 0) {
      myArray[0] = newValue;
    }
    else {
      if (newValue > myArray[0]) {
        myArray[1] = newValue;
      }
      else {
        myArray[1] = myArray[0];
        myArray[0] = newValue;
      }
    }
    numEntries++;
    return numEntries;
  }
  for (int i = 0; i < numEntries; i++) {
    if (newValue >= myArray[i] && newValue <= myArray[i+1]) {
      for (int j = numEntries; j > i+1; j--) {
        myArray[j] = myArray[j-1];
      }
      myArray[i+1] = newValue;
      numEntries++;
      for (int k = 0; k < numEntries; k++) {
      }
      return numEntries;
    }
  }
}

void numberSorter(string fileName) {
  ifstream file;
  file.open(fileName);
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

int main() {
  numberSorter("numbers.txt");
//   // int array[100] = {8};
//   // insertIntoSortedArray(array, 1, 6);
}
