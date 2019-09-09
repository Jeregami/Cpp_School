#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

struct wordItem {
  string word;
  int count;
};

void doubleArray(wordItem uniqueWords[], int length);
void getStopWords(const char *ignoreWordFileName, string ignoreWords[]);
bool isStopWord(string word, string ignoreWords[]);
int getTotalNumberNonStopWords(wordItem uniqueWords[], int length);
void arraySort(wordItem uniqueWords[], int length);
void printNext10(wordItem uniqueWords[], int N, int totalNumWords);


int main(int argc, char const *argv[]) {
  if (argc != 3 ) {
    cout << "Usage: Assignment2Solution " << argv[0] << " " << argv[1] << " " << argv[2] << endl;
    return 0;
  }
  string ignoreWords[50];
  getStopWords(argv[2], ignoreWords);
  int numTimesWordArrayDoubled = 0;
  wordItem uniqueWords[100];
  int numUniqueWords = 0;
  ifstream file(argv[1]);
  string lineData;
  while (getline(file, lineData)) {
    istringstream ss(lineData);
    string word;
    while (getline(ss, word, ' ')) {
      if (isStopWord(word, ignoreWords) == 0) {
        // If the uniqueWords array is full, then double the size of the array
        if (numUniqueWords == 100 * (pow(2, numTimesWordArrayDoubled))) {

        }
        for (int i = 0; i < numUniqueWords+1; i++) {
          if (i == numUniqueWords) {
            uniqueWords[i].word = word;
            uniqueWords[i].count++;
          }
          if (uniqueWords[i].word == word) {
            uniqueWords[i].count++;
          }
        }
      }
    }
  }
  for (int i = 0; i < 25; i++) {
    cout << uniqueWords[i].word << " ";
  }
}


void doubleArray(wordItem uniqueWords[], int length) {
  wordItem* newArray = new wordItem[length*2];
  for (int i = 0; i < length; i++) {
    newArray[i] = uniqueWords[i];
  }
  delete[] uniqueWords;
  uniqueWords = newArray;
}


// Reads from a file of stop words and puts them into the ignoreWords array
void getStopWords(const char *ignoreWordFileName, string ignoreWords[]) {
  ifstream file(ignoreWordFileName);
  if (!file.is_open()) {
    cout << "Failed to open " << ignoreWordFileName << endl;
  }
  string lineData;
  int count = 0;
  while (getline(file, lineData)) {
    ignoreWords[count] = lineData;
    count++;
  }
  file.close();
}


// Checks if a given word is part of the ignoreWords array
bool isStopWord(string word, string ignoreWords[]) {
  for (int i = 0; i < 50; i++) {
    if (ignoreWords[i] == word) {
      return 1;
    }
  }
  return 0;
}


// Returns the total number of non stop words in the document
int getTotalNumberNonStopWords(wordItem uniqueWords[], int length) {

}


void arraySort(wordItem uniqueWords[], int length) {

}


void printNext10(wordItem uniqueWords[], int N, int totalNumWords) {

}
