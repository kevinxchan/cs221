// file:        stack.h
// author:      Geoff T
// date:        2017-10-08
// description: declaration of a stack class for CPSC 221 PA2
//              This file should not be modified
//              If you want to implement private helper functions,
//                you may do so in stackprivate.h

#ifndef _STACK_H_
#define _STACK_H_

#include "arrayclass.h"

template <typename T>
class Stack
{
  private:
    ArrayClass<T> ac;

    #include "stackprivate.h" // define and implement your private
                              // member functions in this file

  public:
    // default constructor
    Stack();

    // copy constructor
    Stack(const Stack& st);

    // assignment operator
    Stack& operator=(const Stack& st);

    ///////////////
    // accessors //
    ///////////////

    // Return true if the stack contains no items
    bool isEmpty() const;

    // Returns the number of items stored in the stack
    unsigned int size() const;

    // Return a reference to the top item of the stack
    // Throws an out_of_range exception if the stack is empty
    T& peek();

    //////////////
    // mutators //
    //////////////

    // Pushes an item to the top of the stack
    void push(const T item);

    // Removes and returns (a copy of) the top item of the stack
    // Throws an out_of_range exception if the stack is empty
    T pop();
};

#include "stack.cpp"

#endif