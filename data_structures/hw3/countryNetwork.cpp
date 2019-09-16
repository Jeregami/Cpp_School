/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represet communication paths between nations             */
/****************************************************************/

#include "countryNetwork.hpp"

using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork() {
  Country *head;
}


/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
void CountryNetwork::insertCountry(Country* previous, string countryName) {
  Country *country = new Country;
  country->name = countryName;
  if (previous == NULL) {
    cout << "adding: " << countryName << " (HEAD)" << endl;
    head = country;
  }
  else {
    cout << "adding: " << countryName << " (prev: " << previous->name << ")" << endl;
    previous->next = country;
  }
}

/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup() {
  insertCountry(NULL, "United States");
  insertCountry(head, "Canada");
  insertCountry(head->next, "Brazil");
  insertCountry(head->next->next, "India");
  insertCountry(head->next->next->next, "China");
  insertCountry(head->next->next->next->next, "Australia");
}

/*
 * Purpose: Search the network for the specified country and return a pointer to that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 */
Country* CountryNetwork::searchNetwork(string countryName) {
  int i = 0;
  Country *ptr = new Country;
  ptr = head;
  while (i < 20) {
    if (ptr->name == countryName) {
      return ptr;
    }
    else if (ptr->name == "") {
      return NULL;
    }
    else {
      ptr = ptr->next;
    }
    i++;
  }
}

/*
 * Purpose: Transmit a message across the network to the
 *   receiver. Msg should be stored in each country it arrives
 *   at, and should increment that country's count.
 * @param receiver name of the country to receive the message
 * @param message the message to send to the receiver
 * @return none
 */
void CountryNetwork::transmitMsg(string receiver, string message) {
  
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath() {

}


int main() {
  CountryNetwork network;
  network.loadDefaultSetup();
  network.searchNetwork("China");

}
