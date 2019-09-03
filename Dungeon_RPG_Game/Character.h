#include <iostream>
#include "Equipment.cpp"
#include "Item.cpp"
using namespace std;

class Character {
private:
    string name;
    int maxHealth;
    int health;
    int regen;
    int attack;
    int defense;
    int gold;
    int accuracy;
    int maxItems;
    int numHeldItems;
    Item item[10];
    Equipment equipment[4];
    string haveEquipment[4];
public:
    // Constructor
    Character();

    // Getters
    string getName();
    int getMaxHealth();
    int getHealth();
    int getRegen();
    int getAttack();
    int getDefense();
    int getGold();
    int getAccuracy();
    int getNumHeldItems();
    Item getItem(int index);
    Equipment getEquipment(int index);

    // Setters
    void setName(string characterName);
    void setMaxHealth(int characterMaxHealth);
    void setHealth(int characterHealth);
    void setRegen(int characterRegen);
    void setAttack(int characterAttack);
    void setDefense(int characterDefense);
    void setGold(int characterGold);
    void setAccuracy(int characterAccuracy);
    void setNumHeldItems(int characterNumHeldItems);
    int setItem(Item newItem);
    int setEquipment(Equipment newEquipment);
};
