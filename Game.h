#include <iostream>
#include <fstream>
#include "Character.cpp"
#include "Floor.cpp"

class Game {
private:
    Character player;
    Effect effect[8];
    int numEffects;
    Floor floors[4];
    int numFloors;
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
    void readFloor();
    void createCharacter();
};