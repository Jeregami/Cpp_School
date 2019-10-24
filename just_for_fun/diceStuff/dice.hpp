#include <iostream>

using namespace std;

struct Die {
  int numSides;
  int numDice;
  Die(int sides, int dice) {
    numSides = sides;
    numDice = dice;
  }
}
