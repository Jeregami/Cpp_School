#include <iostream>
#include "QUEUEST.hpp"
using namespace std;


Queue::Queue()
{

}
Queue::~Queue()
{
  while(!isEmpty())
    dequeue();
}

/**
* This function will create the queue of size cap
* parameter: int cap
* return void
**/
void Queue:: initialiseQueue(int cap)
{
  primary.initialise(cap);
  secondary.initialise(cap);
}

/**
* This function will enqueue the argument num
* parameter: int num
* return void
**/
void Queue:: enqueue(int num){
    if(isFull())
    {
      cout<< " Queue is full. Can not enqueue"<<endl;
      return;
    }
    primary.push(num);
}
/**
* This function will dequeue from the queue.
* parameter: None
* return the dequeued value
* TODO: Implement this function
**/
int Queue:: dequeue(){
  // If the queue is empty
  if (isEmpty()) {
    cout << "Queue is empty." << endl;
    return -999;
  }
  else {
    // set the number to be the top of the queue
    Queue* temp = new Queue;
    // while the queue has more than one number, enqueue top number into different Queue
    while (secondary.peek() != 0) {
      int number = primary.peek();
      temp->enqueue(number);
    }
    int top = primary.peek();
    primary.pop();
    return top;
  }
}
/**
* returns true if queue is full
**/
bool Queue:: isFull(){
  return primary.isFull();
}

/**
* returns true if queue is full.
**/
bool Queue:: isEmpty(){
  return primary.isEmpty();
}
