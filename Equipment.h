#include <iostream>
using namespace std;

class Equipment {
private:
    string name;
    string type;
    int effectiveness;
    string normalEffect;
    int normalValue;
    string specialEffect;
    int specialValue;
public:
    // Constructor
    Equipment();
    
    // Getters
    string getName();
    string getType();
    int getEffectiveness();
    string getNormalEffect();
    int getNormalValue();
    string getSpecialEffect();
    int getSpecialValue();
    
    // Setters
    void setName(string equipmentName);
    void setType(string equipmentType);
    void setEffectiveness(int equipmentEffectiveness);
    void setNormalEffect(string equipmentNormalEffect);
    void setNormalValue(int equipmentNormalValue);
    void setSpecialEffect(string equipmentSpecialEffect);
    void setSpecialValue(int equipmentSpecialValue);
};