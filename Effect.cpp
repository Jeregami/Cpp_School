#include <iostream>
#include "Effect.h"
using namespace std;

// Constructor

Effect::Effect() {
    name = "";
    stat = "";
    goodOrBad = "";
    effectiveness = "";
    length = 0;
}


// Getters 

string Effect::getName() {
    return name;
}

string Effect::getStat() {
    return stat;
}

string Effect::getGoodOrBad() {
    return goodOrBad;
}

string Effect::getEffectiveness() {
    return effectiveness;
}

int Effect::getLength() {
    return length;
}


// Setters

void Effect::setName(string effectName) {
    name = effectName;
}

void Effect::setStat(string effectStat) {
    stat = effectStat;
}

void Effect::setGoodOrBad(string effectGoodOrBad) {
    goodOrBad = effectGoodOrBad;
}

void Effect::setEffectiveness(string effectEffectiveness) {
    effectiveness = effectEffectiveness;
}

void Effect::setLength(int effectLength) {
    length = effectLength;
}