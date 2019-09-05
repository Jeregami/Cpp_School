#include <iostream>
#include <fstream>
#include <sstream>
#include "Game.h"
using namespace std;


// Function to help read txt files
int split(string message, string arr[], int lengthOfArray, char split) {
    if (message.length() == 0) {
        return 0;
    }
    string currentString = "";
    int count = 0;
    message = message + split;
    for (int i = 0; i < message.length(); i++) {
        if (message[i] == split) {
            if (currentString.length() == 0) continue;
            arr[count] = currentString;
            count++;
            currentString = "";
        }
        else {
            currentString = currentString + message[i];
        }
    }
    if (count > lengthOfArray) {
        return -1;
    }
    else {
        return count;
    }
}


// Constructor

Game::Game() {
    numEffects = 8;
    numFloors = 4;
    numEquipment = 17;
}


// Getters

int Game::getRandomNumber() {
    srand(time(0));
    return rand();
}

Character Game::getPlayer() {
    return player;
}

Effect Game::getRandomEffect(int index, int effectiveness) {

}

Floor Game::getFloor(int index) {
    return floor[index];
}

Item Game::getRandomItem(int index, Effect randomEffect) {

}

Equipment Game::getRandomEquipment(int index, Effect randomEffect) {

}


// Setters

void Game::readEffects() {
  ifstream file;
  file.open("effects.txt");
  string lineData;
  while (getline(file, lineData)) {
      string arr[4];
      split(lineData, arr, 4, ',');
      for (int i = 0; i < numEffects; i++) {
          effect[i].setName(arr[0]);
          effect[i].setStat(arr[1]);
          effect[i].setEffectiveness(stoi(arr[2]));
          effect[i].setGoodOrBad(arr[3]);
      }
  }
  file.close();
}

void Game::readEquipment() {
  ifstream file;
  file.open("equipment.txt");
  string lineData;
  while (getline(file, lineData)) {
    string arr[5];
    split(lineData, arr, 4, ',');
    for (int i = 0; i < numEquipment; i++) {
      equipment[i].setName(arr[0]);
      equipment[i].setType(arr[1]);
      equipment[i].setNormalValue(stoi(arr[2]));
      equipment[i].setSpecialEffect(arr[3]);
      equipment[i].setSpecialValue(stoi(arr[4]));
    }
  }
  file.close();
}

void Game::readFloor(string fileName, int floorNumber) {
  ifstream file;
  file.open(fileName);
  string lineData;
  int row = 0;
  int column = 0;
  while (getline(file, lineData)) {
    istringstream ss(lineData);
    string data;
    while (getline(ss, data, ',')) {
      floor[floorNumber-1].setCoordinates(row, column, data);
      column++;
    }
    row++;
  }
}


void Game::printFloor(int floorNumber) {
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      cout << floor[floorNumber-1].getCoordinates(i,j);
    }
    cout << endl;
  }
}


void Game::createCharacter() {

}
