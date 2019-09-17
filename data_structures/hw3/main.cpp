#include "countryNetwork.cpp"

// declarations for main helper-functions
void displayMenu();

int main(int argc, char* argv[]) {
    // Object representing our network of cities.
    CountryNetwork network;

    // Variables to hold inputed values
    string message;
    string country;
    string newCountry;
    string previousName;
    Country *previous = new Country;

    string choice;
    while (choice != "5") {
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
          cout << "Enter name of the country to receive the message:" << endl;
          getline(cin, country);
          cout << "Enter the message to send" << endl;
          getline(cin, message);
          cout << endl;
          network.transmitMsg(country, message);
          break;
        case 4:
          cout << "Enter a new country name:" << endl;
          getline(cin, newCountry);
          toupper(newCountry[0]);
          for (int i = 1; i < newCountry.length(); i++) {
            tolower(newCountry[i]);
          }
          cout << "Enter the previous country name (or First):" << endl;
          while (0 < 1) {
            getline(cin, previousName);
            toupper(previousName[0]);
            for (int i = 1; i < previousName.length(); i++) {
              tolower(previousName[i]);
            }
            if (previousName == "First") {
              network.insertCountry(NULL, newCountry);
              break;
            }
            else if (network.searchNetwork(previousName) == NULL) {
              cout << "INVALID(previous country name)...Please enter a VALID previous country name!" << endl;
            }
            else {
              previous = network.searchNetwork(previousName);
              break;
            }
          }
          network.insertCountry(previous, newCountry);
          network.printPath();
        case 5:
          cout << "Quitting..." << endl;
          break;
        default:
          cout << "Invalid Input" << endl;
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
    cout << " 3. Transmit Message " << endl;
    cout << " 4. Add Country " << endl;
    cout << " 5. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
