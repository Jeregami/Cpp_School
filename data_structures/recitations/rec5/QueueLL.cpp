#include <iostream>
#include "QueueLL.hpp"

using namespace std;

QueueLL::QueueLL()
{
    queueFront = nullptr;
    queueEnd = nullptr;
}

QueueLL::~QueueLL()
{
    while( !isEmpty() )
        dequeue();
}

bool QueueLL::isEmpty()
{
    /*if(queueFront == nullptr || queueEnd == nullptr)
        return true;
    return false;*/
    return (!queueFront || !queueEnd);
}

// TODO
void QueueLL::enqueue(int key) {
    Node *nn = new Node;
    nn->key = key;
    nn->next = nullptr;
    if (queueEnd == NULL) {
      if (queueFront == NULL) {
        queueFront = nn;
      }
      else {
        queueEnd = nn;
        queueFront->next = queueEnd;
      }
    }
    else {
      queueEnd->next = nn;
      queueEnd = nn;
    }
}

//TODO
void QueueLL::dequeue() {
    if(!isEmpty()) {
      queueFront = queueFront->next;
    }
    else {
        cout<<"queue is empty. cannot dequeue"<<endl;
    }
}

int QueueLL::peek()
{
    if( !isEmpty() )
        return queueFront->key;
    else
    {
        cout<< " queue is empty. can not peek"<<endl;
        return -1;
    }
    //return 0;
}
