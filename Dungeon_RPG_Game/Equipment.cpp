#include <iostream>
#include "Equipment.h"
using namespace std;

// Constructor

Equipment::Equipment() {
    name = "";
    type = "";
    effectiveness = 0;
    normalEffect = "";
    normalValue = 0;
    specialEffect = "";
    specialValue = 0;
}


// Getters

string Equipment::getName() {
    return name;
}

string Equipment::getType() {
    return type;
}

int Equipment::getEffectiveness() {
    return effectiveness;
}

string Equipment::getNormalEffect() {
    return normalEffect;
}

int Equipment::getNormalValue() {
    return normalValue;
}

string Equipment::getSpecialEffect() {
    return specialEffect;
}

int Equipment::getSpecialValue() {
    return specialValue;
}


// Setters

void Equipment::setName(string equipmentName) {
    name = equipmentName;
}

void Equipment::setType(string equipmentType) {
    type = equipmentType;
}

void Equipment::setEffectiveness(int equipmentEffectiveness) {
    effectiveness = equipmentEffectiveness;
}

void Equipment::setNormalEffect(string equipmentNormalEffect) {
    normalEffect = equipmentNormalEffect;
}

void Equipment::setNormalValue(int equipmentNormalValue) {
    normalValue = equipmentNormalValue;
}

void Equipment::setSpecialEffect(string equipmentSpecialEffect) {
    specialEffect = equipmentSpecialEffect;
}

void Equipment::setSpecialValue(int equipmentSpecialValue) {
    specialValue = equipmentSpecialValue;
}