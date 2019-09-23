/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represet communication paths between nations             */
/****************************************************************/

#include "CountryNetwork.hpp"

using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork() {
  head = NULL;
}


/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CountryNetwork::isEmpty() {
}


/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
 void CountryNetwork::insertCountry(Country* previous, string countryName) {
   Country *newCountry = new Country;
   newCountry->name = countryName;
   // Insert at beginning
   if (previous == NULL) {
     cout << "adding: " << countryName << " (HEAD)" << endl;
     // If list is empty
     if (head == NULL) {
       head = new Country;
       head->name = countryName;
       head->next = NULL;
     }
     // If list is not empty
     else {
       previous->next = newCountry;
       head = newCountry;
     }
   }
   else {
     cout << "adding: " << countryName << " (prev: " << previous->name << ")" << endl;
     // Insert anywhere else
     newCountry->next = previous->next;
     previous->next = newCountry;
   }
 }


/*
 * Purpose: delete the country in the network with the specified name.
 * @param countryName name of the country to delete in the network
 * @return none
 */
void CountryNetwork::deleteCountry(string countryName) {
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
 * @see insertCountry, deletecountry
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
 * Purpose: deletes all countries in the network starting at the head country.
 * @param none
 * @return none
 */
void CountryNetwork::deleteEntireNetwork() {
}

/*
 * Purpose: Rotate the linked list i.e. move 'n' elements from
 * the back of the the linked to the front in the same order.
 * @param number elements to be moved from the end of the list to the beginning
 * @return none
 */
 void CountryNetwork :: rotateNetwork(int n) {
}

/*
 * Purpose: reverse the entire network
 * @param ptr head of list
 */
void CountryNetwork::reverseEntireNetwork() {
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath() {
  Country *ptr = new Country;
  int i = 0;
  cout << "== CURRENT PATH ==" << endl;
  if (head == NULL) {
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
