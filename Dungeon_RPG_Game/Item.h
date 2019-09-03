#include <iostream>
#include "Effect.cpp"
using namespace std;

class Item {
private:
    string name;
    int quantity;
    Effect effect;
public:
    // Constructor
    Item();
    
    // Getters
    string getName();
    int getQuantity();
    Effect getEffect();
    
    // Setters
    void setName(string itemName);
    void setQuantity(int itemQuantity);
    void setEffect(Effect itemEffect);
};