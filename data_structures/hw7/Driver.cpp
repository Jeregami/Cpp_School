#include <iostream>
#include <sstream>
#include <fstream>
#include "MovieTree.cpp"

using namespace std;

void menu() {
  cout << "======Main Menu======" << endl;
  cout << "1. Print the inventory" << endl;
  cout << "2. Delete a movie" << endl;
  cout << "3. Quit" << endl;
}

int main(int argc, char const *argv[]) {
  if (argc != 2) {
    cout << "Incorrect usage. Be sure to include the file to read from on the command line" << endl;
    return 0;
  }
  MovieTree tree;
  ifstream file(argv[1]);
  if (!file.is_open()) {
    cout << "The file " << argv[1] << " does not exist." << endl;
    return 0;
  }
  string lineData;
  string array[4];
  int index = 0;
  while (getline(file, lineData)) {
    istringstream ss(lineData);
    string word;
    index = 0;
    while (getline(ss, word, ',')) {
      array[index] = word;
      index++;
    }
    tree.addMovie(stoi(array[0]), array[1], stoi(array[2]), stof(array[3]));
  }
  tree.printMovieInventory();
  return 0;
  // Variables to store user input
  string choice;
  string title;

  while (choice != "3") {
    menu();
    getline(cin, choice);
    int choiceNumber = stoi(choice);
    switch(choiceNumber) {
      case 1:
        tree.printMovieInventory();
        break;
      case 2:
        cout << "Enter a movie title:" << endl;
        getline(cin, title);
        tree.deleteMovie(title);
        break;
      case 3:
        cout << "Goodbye!" << endl;
        break;
    }
  }
}
