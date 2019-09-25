/****************************************************************/
/*                   Assignment 4 Driver File                   */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "countryNetwork.cpp"

using namespace std;

void displayMenu();

int main() {
    // Object representing our network of cities.
    // (Linked list representation is in CountryNetwork)
    CountryNetwork network;

    // Variables to hold inputed variables
    string rotationChoice;
    int rotation;
    string countryName;
    string previousName;
    Country *previous = new Country;

    string choice;
    while (choice != "8") {
      displayMenu();
      getline(cin, choice);
      int menuChoice = stoi(choice);
      switch (menuChoice) {
        case 1:
          network.loadDefaultSetup();
          network.printPath();
          break;
        case 2:
          network.printPath();
          break;
        case 3:
          cout << "Enter a new country name:" << endl;
          getline(cin, countryName);
          toupper(countryName[0]);
          for (int i = 1; i < countryName.length(); i++) {
            tolower(countryName[i]);
          }
          cout << "Enter the previous country name (or First):" << endl;
          while (0 < 1) {
            getline(cin, previousName);
            toupper(previousName[0]);
            for (int i = 1; i < previousName.length(); i++) {
              tolower(previousName[i]);
            }
            if (previousName == "First") {
              network.insertCountry(NULL, countryName);
              break;
            }
            else if (network.searchNetwork(previousName) == NULL) {
              cout << "INVALID(previous country name)...Please enter a VALID previous country name!" << endl;
            }
            else {
              previous = network.searchNetwork(previousName);
              network.insertCountry(previous, countryName);
              break;
            }
          }
          network.printPath();
          break;
        case 4:
          cout << "Enter a country name:" << endl;
          getline(cin, countryName);
          network.deleteCountry(countryName);
          network.printPath();
          break;
        case 5:
          network.reverseEntireNetwork();
          network.printPath();
          break;
        case 6:
          cout << "Enter the count of values to be rotated:" << endl;
          getline(cin, rotationChoice);
          rotation = stoi(rotationChoice);
          network.rotateNetwork(rotation);
          network.printPath();
          break;
        case 7:
          cout << "Network before deletion" << endl;
          network.printPath();
          network.deleteEntireNetwork();
          cout << "Network after deletion" << endl;
          network.printPath();
          break;
        case 8:
          cout << "Quitting... cleaning up path: " << endl;
          network.deleteEntireNetwork();
          network.printPath();
          if (network.isEmpty() == true) {
            cout << "Path cleaned" << endl;
          }
          else {
            cout << "Error: Path NOT cleaned" << endl;
          }
          break;
      }
    }
    cout << "Goodbye!" << endl;
    return 0;
}

/*
 * Purpose; displays a menu with options
 */
void displayMenu() {
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Add Country " << endl;
    cout << " 4. Delete Country " << endl;
    cout << " 5. Reverse Network" << endl;
    cout << " 6. Rotate Network" << endl;
    cout << " 7. Clear Network " << endl;
    cout << " 8. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
