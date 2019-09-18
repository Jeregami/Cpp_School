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
  country->next = NULL;
  if (previous == NULL) {
    cout << "adding: " << countryName << " (HEAD)" << endl;
    if (head != NULL) {
      country->next = head;
    }
    head = country;
  }
  else {
    cout << "adding: " << countryName << " (prev: " << previous->name << ")" << endl;
    // If previous is the tail
    if (previous->next == NULL) {
      previous->next = country;
    }
    // If country is inserted somewher in middle
    else {
      country->next = previous->next;
      previous->next = country;
    }
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
  if (head == NULL) {
    return NULL;
  }
  int i = 0;
  Country *ptr = new Country;
  ptr = head;
  while (i < 100) {
    if (ptr->name == countryName) {
      return ptr;
    }
    else if (ptr->next == NULL) {
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
  if (head == NULL) {
    cout << "Empty list" << endl;
  }
  else if (searchNetwork(receiver) == NULL) {
    cout << "Country not found" << endl;
  }
  else {
    int i = 0;
    Country *ptr = new Country;
    ptr = head;
    while (i < 100) {
      ptr->message = message;
      ptr->numberMessages++;
      cout << ptr->name << " [# messages received: " << ptr->numberMessages << "] received: " << ptr->message << endl;
      if (ptr->name != receiver) {
        ptr = ptr->next;
      }
      else if (ptr->name == receiver) {
        i = 100;
      }
      i++;
    }
  }
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath() {
  Country *ptr = new Country;
  int i = 0;
  cout << "== CURRENT PATH ==" << endl;
  if (head->next == NULL) {
    cout << "nothing in path" << endl;
  }
  else {
    ptr = head;
    while (i < 100) {
      cout << ptr->name << " -> ";
      if (ptr->next == NULL) {
        cout << "NULL" << endl;
        break;
      }
      ptr = ptr->next;
      i++;
    }
  }
  cout << "===" << endl;
}
