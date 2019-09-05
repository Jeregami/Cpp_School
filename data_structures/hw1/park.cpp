#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Park {
  string parkname;
  string state;
  int area;
};

// Adds a new park structure to an array of parks
void addPark(Park parks[], string parkname, string state, int area, int length) {
  Park newPark;
  newPark.parkname = parkname;
  newPark.state = state;
  newPark.area = area;
  parks[length] = newPark;
}

// Prints the list of parks
void printList(const Park parks[], int length) {
  for (int i = 0; i < length; i++) {
    cout << parks[i].parkname << " [" << parks[i].state << "] area: " << parks[i].area << endl;
  }
}

// Arguments: Input file name, output file name, minimum area of parks to be written to output file
int main(int argc, char *argv[]) {
  string line;
  ifstream inputFile(argv[1]);
  if (!inputFile.is_open()) {
    cout << argv[1] << " does not exist" << endl;
    return 0;
  }
  Park parks[100];
  int numParks = 0;
  while (getline(inputFile, line)) {
    string arr[3];
    istringstream ss(line);
    string data;
    int count = 0;
    while (getline(ss, data, ',')) {
      arr[count] = data;
      count++;
    }
    addPark(parks, arr[0], arr[1], stoi(arr[2]), numParks);
    numParks++;
  }
  inputFile.close();
  printList(parks, numParks);
  ofstream outputFile(argv[2]);
  if (!outputFile.is_open()) {
    cout << argv[2] << "does not exist" << endl;
    return 0;
  }
  int minArea = stoi(argv[3]);
  for (int i = 0; i < numParks; i++) {
    if (parks[i].area > minArea) {
      outputFile << parks[i].parkname << "," << parks[i].state << "," << parks[i].area << endl;
    }
  }
}
