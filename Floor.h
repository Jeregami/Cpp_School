#include <iostream>
using namespace std;

class Floor {
private:
    string coordinates[100][100];
    string hidden[100][100];
    int numRows;
    int numColumns;
public:
    // Constructor
    Floor();
    
    // Getters
    string getCoordinates(int row, int column);
    string getHidden(int row, int column);
    
    // Setters
    void setCoordinates(int row, int column, string mark);
    void setHidden(int row, int column, string mark);
};