#include <iostream>
#include <fstream>
#include "Character.cpp"
#include "Floor.cpp"

class Game {
private:
    Character player;
    Effect effect[8];
    int numEffects;
    Floor floor[4];
    int numFloors;
    Equipment equipment[17];
    int numEquipment;
public:
    // Constructor
    Game();

    // Getters
    int getRandomNumber();
    Character getPlayer();
    Effect getRandomEffect(int index, int effectiveness);
    Floor getFloor(int index);
    Item getRandomItem(int index, Effect randomEffect);
    Equipment getRandomEquipment(int index, Effect randomEffect);

    // Setters
    void readEffects();
    void readEquipment();
    void readFloor(string fileName, int floorNumber);
    void printFloor(int floorNumber);
    void createCharacter();
};
