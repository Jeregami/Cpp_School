#include "RPNCalculator.hpp"
#include <iomanip>

using namespace std;

RPNCalculator::RPNCalculator() {
  stackHead = NULL;
}

RPNCalculator::~RPNCalculator() {
  while (0 < 1) {
    if (stackHead != NULL) {
      stackHead = stackHead->next;
    }
    else {
      break;
    }
  }
}

bool RPNCalculator::isEmpty() {
  if (stackHead == NULL) {
    return true;
  }
  else {
    return false;
  }
}

void RPNCalculator::push(float number) {
  Operand *node = new Operand;
  node->number = number;
  node->next = NULL;
  if (isEmpty()) {
    stackHead = node;
  }
  else {
    node->next = stackHead;
    stackHead = node;
  }
}

void RPNCalculator::pop() {
  if (isEmpty()) {
    cout << "Stack empty, cannot pop an item." << endl;
  }
  else {
    stackHead = stackHead->next;
  }
}

Operand* RPNCalculator::peek() {
  if (isEmpty()) {
    cout << "Stack empty, cannot peek." << endl;
    return NULL;
  }
  else {
    return stackHead;
  }
}

bool RPNCalculator::compute(string symbol) {
  if (symbol != "+") {
    if (symbol != "*") {
      cout << "err: invalid operation" << endl;
      return false;
    }
  }
  float number1;
  float number2;
  for (int i = 0; i < 2; i++) {
    if (stackHead == NULL) {
      cout << "err: not enough operands" << endl;
      if (i == 1) {
        push(number1);
      }
      return false;
    }
    else {
      if (i == 0) {
        number1 = stackHead->number;
      }
      number2 = stackHead->number;
      pop();
    }
  }
  float calculation;
  if (symbol == "+") {
    calculation = number1 + number2;
  }
  else if (symbol == "*") {
    calculation = number1 * number2;
  }
  push(calculation);
  return true;
}
