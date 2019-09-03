#include <iostream>
#include "Floor.h"

// Constructor

Floor::Floor() {
    int numRows = 100;
    int numColumns = 100;
}


// Getters

string Floor::getCoordinates(int row, int column) {
    return coordinates[row][column];
}

string Floor::getHidden(int row, int column) {
    return hidden[row][column];
}


// Setters

void Floor::setCoordinates(int row, int column, string mark) {
    coordinates[row][column] = mark;
}

void Floor::setHidden(int row, int column, string mark) {
    hidden[row][column] = mark;
}