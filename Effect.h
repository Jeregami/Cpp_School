#include <iostream>
using namespace std;

class Effect {
private:
    string name;
    string stat;
    string goodOrBad;
    string effectiveness;
    int length;
public:
    // Constructor
    Effect();
    
    // Getters
    string getName();
    string getStat();
    string getGoodOrBad();
    string getEffectiveness();
    int getLength();
    
    // Setters
    void setName(string effectName);
    void setStat(string effectStat);
    void setGoodOrBad(string effectGoodOrBad);
    void setEffectiveness(string effectEffectiveness);
    void setLength(int effectLength);
};