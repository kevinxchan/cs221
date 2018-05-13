// file:        arrayclass.h
// author:      Geoff T
// date:        2017-10-06
// description: declaration of a dynamic array class for CPSC 221 PA2
//              This file should not be modified
//              If you want to implement private helper functions,
//                you may do so in arrayclassprivate.h

#ifndef _ARRAYCLASS_H_
#define _ARRAYCLASS_H_

#define DEFAULTCAPACITY 4
#define EXPANSIONFACTOR 2

#include <algorithm>
#include <cstdlib>
#include <stdexcept>

template <typename T>
class ArrayClass
{
  private:
    unsigned int _capacity; // maximum capacity of the array
    unsigned int _size;     // number of elements stored in the array
    T* arr;                 // dynamic array

    // helper method for deep copy
    void copyArray(const ArrayClass& ac);

    // helper method for expanding array
    void expandArray();

    #include "arrayclassprivate.h" // define and implement your private
                                   // member functions in this file

  public:
    // default constructor
    // Creates an empty ArrayClass with DEFAULTCAPACITY
    ArrayClass();

    // parameterized constructor
    // Creates an empty ArrayClass with capacity of n
    ArrayClass(unsigned int n);

    // copy constructor
    // Creates an ArrayClass as a deep copy of the parameter
    ArrayClass(const ArrayClass& ac);

    // destructor
    ~ArrayClass();

    // overloaded assignment operator
    ArrayClass& operator=(const ArrayClass& ac);

    ////////////////////////
    // capacity functions //
    ////////////////////////

    // Returns the number of elements stored in the array
    unsigned int size() const;

    // Returns the maximum capacity of the array
    unsigned int capacity() const;

    // Resizes the array
    // If n is smaller than the size, then only the
    //   first n elements are copied to the new array
    void resize(unsigned int n);

    // Check if array is empty
    // return true if array is empty
    bool empty() const;

    // Resizes the array to fit exactly as many items
    //   as are stored in the array
    void shrinkToFit();

    //////////////////////////////
    // element access functions //
    //////////////////////////////

    // Returns a reference to the element at position i
    //   in the array.
    // Throws an out_of_range exception if i is outside
    //   the bounds of valid elements
    T& operator[](unsigned int i);

    // Returns a reference to the element at position i
    //   in the array.
    // Throws an out_of_range exception if i is outside
    //   the bounds of valid elements
    T& at(unsigned int i);

    // Returns a reference to the first element in the array
    // Calling this on an empty array throws out_of_range exception
    T& front();

    // Returns a reference to the last element in the array
    // Calling this on an empty array throws out_of_range exception
    T& back();

    //////////////////////
    // modify functions //
    //////////////////////

    // Add an element at the end
    // If array is at capacity before adding, then
    //   expand the array to double its capacity and
    //   then add.
    void pushBack(const T& item);

    // Removes the last stored element in the array,
    //   reducing container size by 1.
    // No effect if called on an empty container
    void popBack();

    // Inserts an element before the element at specified position
    // Expands the array if necessary
    // Elements to the right of position (inclusive) must be shifted
    // Throws out_of_range if position is > _size
    // POST: item is at position, all elements formerly at position and beyond are shifted
    void insert(unsigned int position, const T& item);

    // Removes an element from the array at specified position.
    // Elements to the right of position will be shifted over to fill the gap
    // Throws out_of_range if position is >= _size
    void erase(unsigned int position);

    // Reallocates stored items into a new array of the same size,
    //   starting from specified position
    // No effect if position is 0 or >= _size
    // e.g. startFrom(3) on {1, 2, 3, 4, 5, 6, 7}
    //   produces {4, 5, 6, 7, 1, 2, 3}
    void startFrom(unsigned int position);
};

#include "arrayclass.cpp"

#endif