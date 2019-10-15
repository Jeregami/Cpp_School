#include "MovieTree.cpp"
#include <iostream>
#include <string>
#include<fstream>
#include <sstream>
#include <stack>

using namespace std;

/* Purpose: displays a menu to the user
  * @param: none
  * @return: none
  */
void menu() {
  cout << "======Main Menu======" << endl;
  cout << "1. Find a movie" << endl;
  cout << "2. Query movies" << endl;
  cout << "3. Print the inventory" << endl;
  cout << "4. Average Rating of movies" << endl;
  cout << "5. Quit" << endl;
}


int main(int argc, char const *argv[]) {
  if (argc != 2) {
    cout << "Incorrect usage. Be sure to include the file to read from on the command line" << endl;
    return 0;
  }
  MovieTree tree;
  ifstream file(argv[1]);
  if (!file.is_open()) {
    cout << "The file " << argv[1] << " does not exist" << endl;
    return 0;
  }
  string lineData;
  string array[4];
  int i = 0;
  while (getline(file, lineData)) {
    i = 0;
    istringstream ss(lineData);
    string word;
    while (getline(ss, word, ',')) {
      array[i] = word;
      i++;
    }
    tree.addMovieNode(stoi(array[0]), array[1], stoi(array[2]), stof(array[3]));
  }
  // Variables to store user input
  string choice;
  string movieTitle;
  string minRating;
  string minYear;

  while (choice != "5") {
    menu();
    getline(cin, choice);
    int menuChoice = stoi(choice);
    switch (menuChoice) {
      case 1:
        cout << "Enter title:" << endl;
        getline(cin, movieTitle);
        tree.findMovie(movieTitle);
        break;
      case 2:
        cout << "Enter minimum rating:" << endl;
        getline(cin, minRating);
        cout << "Enter minimum year:" << endl;
        getline(cin, minYear);
        tree.queryMovies(stof(minRating), stoi(minYear));
        break;
      case 3:
        tree.printMovieInventory();
        break;
      case 4:
        tree.averageRating();
        break;
      case 5:
        cout << "Goodbye!" << endl;
        break;
    }
  }
}
