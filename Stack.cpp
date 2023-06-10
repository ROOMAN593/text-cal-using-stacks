
#include <iostream>
#include "Stack.h"

using namespace std;

Stack::Stack()
{
  topIndex = -1;
}

bool Stack::push(OperationData newValue)
{
  if (topIndex < MAX_STACK_SIZE - 1)
  {
    ++topIndex;
    stackArr[topIndex] = newValue;
    return true;
  }
  else
  {
    return false;
  }
}

OperationData Stack::pop()
{
  // taking advantage of post-increment so we don't have to save the value off to return it
  return stackArr[topIndex--];
}
