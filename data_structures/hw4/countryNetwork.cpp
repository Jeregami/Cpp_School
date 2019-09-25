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
  head = NULL;
}


/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CountryNetwork::isEmpty() {
  if (head == NULL) {
    return true;
  }
  else {
    return false;
  }
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
       newCountry->next = head;
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
  if (searchNetwork(countryName) == NULL) {
    cout << "Country does not exist." << endl;
  }
  else {
    // If country being deleted is the head
    if (head->name == countryName) {
      head = head->next;
    }
    Country *currentCountry = new Country;
    Country *previousCountry = new Country;
    currentCountry = head;
    previousCountry = NULL;
    while (0 < 1) {
      if (currentCountry->next == NULL) {
        if (currentCountry->name == countryName) {
          previousCountry->next = NULL;
        }
        break;
      }
      if (currentCountry->name == countryName) {
        previousCountry->next = currentCountry->next;
        break;
      }
      else {
        previousCountry = currentCountry;
        currentCountry = currentCountry->next;
      }
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
  if (head != NULL) {
    while (0 < 1) {
      cout << "deleting: " << head->name << endl;
      head = head->next;
      if (head == NULL) {
        cout << "Deleted network" << endl;
        break;
      }
    }
  }
}

/*
 * Purpose: Rotate the linked list i.e. move 'n' elements from
 * the back of the the linked to the front in the same order.
 * @param number elements to be moved from the end of the list to the beginning
 * @return none
 */
 void CountryNetwork :: rotateNetwork(int n) {
   if (head == NULL) {
     cout << "Linked List is Empty" << endl;
   }
   else {
     int count = 1;
     Country *current = new Country;
     current = head;
     while (0 < 1) {
       if (current->next == NULL) {
         break;
       }
       count++;
       current = current->next;
     }
     if (n < 1 || n > count) {
       cout << "Rotate not possible" << endl;
     }
     else {
       int g = 0;
       Country *previous = new Country;
       Country *next = new Country;
       for (int k = 0; k < n; k++) {
         for (int i = 0; i < count-1; i++) {
           previous = NULL;
           current = head;
           next = current->next;
           for (int j = 0; j < i; j++) {
             previous = current;
             current = next;
             next = next->next;
           }
           if (previous == NULL) {
             current->next = next->next;
             head = next;
             next->next = current;
           }
           else {
             previous->next = next;
             current->next = next->next;
             next->next = current;
           }
         }
       }
       cout << "Rotate Complete" << endl;
     }
   }
}

/*
 * Purpose: reverse the entire network
 * @param ptr head of list
 */
void CountryNetwork::reverseEntireNetwork() {
  if (isEmpty() == false) {
    Country *headCountry = new Country;
    Country *previousHead = new Country;
    Country *tailCountry = new Country;
    Country *previousTail = new Country;
    tailCountry = head;
    previousTail = NULL;
    int count = 0;
    while (0 < 1) {
      count++;
      if (tailCountry->next == NULL) {
        break;
      }
      else {
        previousTail = tailCountry;
        tailCountry = tailCountry->next;
      }
    }
    headCountry = head;
    for (int i = 0; i < count/2; i++) {
      headCountry = head;
      tailCountry = head;
      previousHead = NULL;
      previousTail = NULL;
      for (int j = 0; j < i; j++) {
        previousHead = headCountry;
        headCountry = headCountry->next;
      }
      for (int j = i; j < count-1; j++) {
        previousTail = tailCountry;
        tailCountry = tailCountry->next;
      }
      if (previousHead == NULL) {
        tailCountry->next = headCountry->next;
        head = tailCountry;
        previousTail->next = headCountry;
        headCountry->next = NULL;
      }
      else if (headCountry->next == tailCountry) {
        previousHead->next = tailCountry;
        headCountry->next = tailCountry->next;
        tailCountry->next = headCountry;
      }
      else {
        Country *temp = new Country;
        temp = tailCountry->next;
        previousHead->next = tailCountry;
        tailCountry->next = headCountry->next;
        previousTail->next = headCountry;
        headCountry->next = temp;
      }
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
