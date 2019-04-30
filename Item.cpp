#include <iostream>
#include "Item.h"
using namespace std;

// Constructor

Item::Item() {
    name = "";
    quantity = 0;
}


// Getters

string Item::getName() {
    return name;
}

int Item::getQuantity() {
    return quantity;
}

Effect Item::getEffect() {
    return effect;
}


// Setters

void Item::setName(string itemName) {
    name = itemName;
}

void Item::setQuantity(int itemQuantity) {
    quantity = itemQuantity;
}

void Item::setEffect(Effect itemEffect) {
    effect = itemEffect;
}