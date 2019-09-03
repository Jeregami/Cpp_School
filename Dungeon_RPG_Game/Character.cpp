#include <iostream>
#include "Character.h"
using namespace std;

// Constructor

Character::Character() {
    name = "";
    maxHealth = 0;
    health = 0;
    regen = 0;
    attack = 0;
    defense = 0;
    accuracy = 0;
    gold = 0;
    maxItems = 10;
    int heldItems = 0;
}


// Getters

string Character::getName() {
    return name;
}

int Character::getMaxHealth() {
    return maxHealth;
}

int Character::getHealth() {
    return health;
}

int Character::getRegen() {
    return regen;
}

int Character::getAttack() {
    return attack;
}

int Character::getDefense() {
    return defense;
}

int Character::getGold() {
    return gold;
}

int Character::getAccuracy() {
    return accuracy;
}

int Character::getNumHeldItems() {
    return numHeldItems;
}

Item Character::getItem(int index) {
    return item[index];
}

Equipment Character::getEquipment(int index) {
    return equipment[index];
}

// Setters

void Character::setName(string characterName) {
    name = characterName;
}

void Character::setMaxHealth(int characterMaxHealth) {
    maxHealth = characterMaxHealth;
}

void Character::setHealth(int characterHealth) {
    health = characterHealth;
}

void Character::setRegen(int characterRegen) {
    regen = characterRegen;
}

void Character::setAttack(int characterAttack) {
    attack = characterAttack;
}

void Character::setDefense(int characterDefense) {
    defense = characterDefense;
}

void Character::setGold(int characterGold) {
    gold = characterGold;
}

void Character::setAccuracy(int characterAccuracy) {
    accuracy = characterAccuracy;
}

void Character::setNumHeldItems(int characterNumHeldItems) {
    numHeldItems = characterNumHeldItems;
}

int Character::setItem(Item newItem) {
    string alreadyHaveItem = "no";
    for (int i = 0; i < numHeldItems; i++) {
        if (newItem.getName() == item[i].getName()) {
            item[i].setQuantity(item[i].getQuantity() + 1);
            alreadyHaveItem = "yes";
        }
    }
    if (alreadyHaveItem == "no") {
        if (numHeldItems == maxItems) {
            // Inventory is full
            return 0;
        }
        else {
            // Picked up a new item
            item[numHeldItems] = newItem;
            return 1;
        }
    }
    // Item already in inventory, added to quantity of item
    return 2;
}

int Character::setEquipment(Equipment newEquipment) {
    if (newEquipment.getType() == "weapon") {
        if (haveEquipment[0] == "no") {
            equipment[0] = newEquipment;
            return 0;
        }
        else {
            return 1;
        }
    }
    else if (newEquipment.getType() == "armor") {
        if (haveEquipment[0] == "no") {
            equipment[0] = newEquipment;
            return 0;
        }
        else {
            return 2;
        }
    }
    else if (newEquipment.getType() == "hat") {
        if (haveEquipment[0] == "no") {
            equipment[0] = newEquipment;
            return 0;
        }
        else {
            return 3;
        }
    }
    else if (newEquipment.getType() == "boots") {
        if (haveEquipment[0] == "no") {
            equipment[0] = newEquipment;
            return 0;
        }
        else {
            return 4;
        }
    }
    // invalid equipment type
    else {
        return -1;
    }
}
