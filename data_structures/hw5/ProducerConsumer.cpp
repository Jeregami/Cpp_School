#include <iostream>
#include "ProducerConsumer.hpp"

using namespace std;

/* Purpose: Sets queueFront and queueEnd to 0
 * @param: none
 * @return: none
 */
ProducerConsumer::ProducerConsumer() {
  queueFront = 0;
  queueEnd = 0;
}

/* Purpose: Figures out if queue is empty
 * @param: none
 * @return: true if empty, false is not
 */
bool ProducerConsumer::isEmpty() {
  if (counter == 0) {
    return true;
  }
  else {
    return false;
  }
}

/* Purpose: Figures out if queue is isFull
 * @param: none
 * @return: true if full, false if not
 */
bool ProducerConsumer::isFull() {
  if (counter == SIZE) {
    return true;
  }
  else {
    return false;
  }
}

/* Purpose: adds item to the queue
 * @param: string item
 * @return: none
 */
void ProducerConsumer::enqueue(string item) {
  if (isFull()) {
    cout << "Queue full, cannot add new item" << endl;
  }
  else {
    if (queueEnd == 20) {
      queueEnd = 0;
    }
    queue[queueEnd] = item;
    queueEnd++;
    counter++;
  }
}

/* Purpose: removes item from the queue
 * @param: none
 * @return: none
 */
void ProducerConsumer::dequeue() {
  if (isEmpty()) {
    cout << "Queue empty, cannot dequeue an item" << endl;
  }
  else {
    queue[queueFront] = "";
    queueFront++;
    if (queueFront == 20) {
      queueFront = 0;
    }
    counter--;
  }
}

/* Purpose: figures out the size of the queue
 * @param: none
 * @return: size of the queue
 */
int ProducerConsumer::queueSize() {
  return counter;
}

/* Purpose: find the item at the front of the queue
 * @param: none
 * @return: string item
 */
string ProducerConsumer::peek() {
  if (isEmpty()) {
    cout << "Queue empty, cannot peek" << endl;
    return "";
  }
  else {
    return queue[queueFront];
  }
}
