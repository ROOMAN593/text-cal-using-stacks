#ifndef STACK_H
#define STACK_H

#include "OperationData.h"

class Stack
{

public:


  Stack(); // constructor

  // add a new value to the stack
  // fails and return false if the stack is full
  bool push(OperationData newValue);

  // pops top item off of the stack
  // Precondition: stack must not be empty
  OperationData pop();

  // return item at the top of the stack without removing it
  // Precondition: stack must not be empty
  OperationData top() { return stackArr[topIndex]; }

  bool isEmpty() { return (topIndex == -1); }

private:
  // private methods would go here

  static const int MAX_STACK_SIZE = 100;
  OperationData stackArr[MAX_STACK_SIZE]; // note can only handle 100 items
  int topIndex;
};

#endif
