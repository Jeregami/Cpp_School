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
  if (argc != 4) {
    cout << "Usage: Assignment2Solution " << argv[0] << " " << argv[1] << " " << argv[2] << endl;
    return 0;
  }
  string ignoreWords[50];
  getStopWords(argv[3], ignoreWords);
  int numTimesWordArrayDoubled = 0;
  wordItem *uniqueWords = new wordItem[100];
  int numUniqueWords = 0;
  int length = 100;
  ifstream file(argv[2]);
  string lineData;
  while (getline(file, lineData)) {
    istringstream ss(lineData);
    string word;
    while (getline(ss, word, ' ')) {
      if (isStopWord(word, ignoreWords) == 0) {
        // If the uniqueWords array is full, then double the size of the array
        if (numUniqueWords == length) {
          length = length * 2;
          wordItem *newArray = new wordItem[length];
          for (int i = 0; i < length/2; i++) {
            newArray[i].word = uniqueWords[i].word;
            newArray[i].count = uniqueWords[i].count;
          }
          uniqueWords = new wordItem[length];
          for (int i = 0; i < length/2; i++) {
            uniqueWords[i].word = newArray[i].word;
            uniqueWords[i].count = newArray[i].count;
          }
          delete [] newArray;
        }
        for (int i = 0; i < numUniqueWords+1; i++) {
          if (i == numUniqueWords) {
            uniqueWords[i].word = word;
            uniqueWords[i].count = 1;
            numUniqueWords++;
            break;
          }
          else if (uniqueWords[i].word == word) {
            uniqueWords[i].count++;
            break;
          }
        }
      }
    }
  }
  file.close();
  int totalNumWords = getTotalNumberNonStopWords(uniqueWords, length);
  arraySort(uniqueWords, length);
  for (int i = 0; i < length; i++) {
    cout << uniqueWords[i].word << " " << uniqueWords[i].count << endl;
  }
  printNext10(uniqueWords, 25, totalNumWords);
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
  int count = 0;
  for (int i = 0; i < length; i++) {
    count = count + uniqueWords[i].count;
  }
  return count;
}


void arraySort(wordItem uniqueWords[], int length) {
  wordItem newArray[length];
  for (int i = 0; i < length; i++) {
    newArray[i].word = uniqueWords[i].word;
    newArray[i].count = uniqueWords[i].count;
  }
  for (int i = 0; i < length; i++) {
    uniqueWords[i].count = 0;
  }
  uniqueWords[0].word = newArray[0].word;
  uniqueWords[0].count = newArray[0].count;
  int numEntries = 1;
  for (int i = 0; i < length; i++) {
    for (int j = 0; j < numEntries+1; j++) {
      if (newArray[i].count > uniqueWords[j].count) {
        for (int k = numEntries; k > j; k--) {
          uniqueWords[k].word = uniqueWords[k-1].word;
          uniqueWords[k].count = uniqueWords[k-1].count;
        }
        uniqueWords[j].word = newArray[i].word;
        uniqueWords[j].count = newArray[i].count;
        numEntries++;
        break;
      }
      else if (uniqueWords[j].count == 0) {
        uniqueWords[j].word = newArray[i].word;
        uniqueWords[j].count = newArray[i].count;
        numEntries++;
        break;
      }
    }
  }
}


void printNext10(wordItem uniqueWords[], int N, int totalNumWords) {
  float probability;
  cout << "Probablity of next 10 words from rank " << N << endl;
  cout << "---------------------------------------" << endl;
  for (int i = N; i < N+10; i++) {
    probability = (float)uniqueWords[i].count / totalNumWords;
    cout << probability << " - " << uniqueWords[i].word << endl;
  }
}
