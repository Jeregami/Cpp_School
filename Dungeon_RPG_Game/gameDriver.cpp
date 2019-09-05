#include <iostream>
#include <fstream>
#include "Game.cpp"
using namespace std;

int main() {
    Game game;
    game.readFloor("floor1.txt", 1);
    game.printFloor(1);
}
