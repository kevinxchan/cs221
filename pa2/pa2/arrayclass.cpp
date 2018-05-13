// file:        arrayclass.cpp
// author:      Geoff T
// date:        2017-10-13
// description: implementation of a dynamic array class for CPSC 221 PA2

#ifdef _ARRAYCLASS_H_

// default constructor
// Creates an empty ArrayClass with DEFAULTCAPACITY
template <typename T>
ArrayClass<T>::ArrayClass()
{
  this->_capacity = DEFAULTCAPACITY;
  this->_size = 0;
  this->arr = new T[this->_capacity];
}

// parameterized constructor
// Creates an empty ArrayClass with capacity of n
template <typename T>
ArrayClass<T>::ArrayClass(unsigned int n)
{
  if (n == 0)
    this->_capacity = 1;
  else
    this->_capacity = n;
  this->_size = 0;
  this->arr = new T[this->_capacity];
}

// copy constructor
// Creates an ArrayClass as a deep copy of the parameter
template <typename T>
ArrayClass<T>::ArrayClass(const ArrayClass& ac)
{
  this->copyArray(ac);
}

// destructor
template <typename T>
ArrayClass<T>::~ArrayClass()
{
  delete[] this->arr; 
  this->arr = NULL;
}

// overloaded assignment operator
template <typename T>
ArrayClass<T>& ArrayClass<T>::operator=(const ArrayClass& ac)
{
  // check for self assignment
  if (&ac != this) {
    this->copyArray(ac);
  }
  return *this;
}

////////////////////////
// capacity functions //
////////////////////////

// Returns the number of elements stored in the array
template <typename T>
unsigned int ArrayClass<T>::size() const
{
  return this->_size;
}

// Returns the maximum capacity of the array
template <typename T>
unsigned int ArrayClass<T>::capacity() const
{
  return this->_capacity;
}

// Resizes the array
// If n is smaller than the size, then only the
//   first n elements are copied to the new array
template <typename T>
void ArrayClass<T>::resize(unsigned int n)
{
  T* tmp;
  // case where invalid index of resizing to 0 occurs
  // change capacity to a minimum of 1
  // change size to 0 (empty array)
  if (n == 0) {
    this->_capacity = 1;
    this->_size = 0;
    // create a new temp array of size 1
    tmp = new T[this->_capacity];
    // delete and point to new array
    // no elements copied over since n == 0
    delete[] this->arr;
    this->arr = tmp;
    return;
  }
  // case where capacity is set to size
  if (n == this->_size) {
    this->_capacity = this->_size;
    return;
  }
  // case where n > size
  // do not need to change size
  else if (n > this->_size) {
    // change capacity to accomodate n
    this->_capacity = n;
    // create temp array with capacity = n elements
    tmp = new T[this->_capacity];
    // copy over all elements
    for (int i = 0; i < this->_size; i++) {
      tmp[i] = this->arr[i];
    }
  }
  // case where 0 < n < size
  else {
    this->_capacity = this->_size = n;
    // create temp array with default capacity
    tmp = new T[this->_capacity];
    // fill the temp array with elements up to n 
  	for (int i = 0; i < this->_size; i++)
  	  tmp[i] = this->arr[i];
  }
  // delete old arr and point to new
  delete[] this->arr; 
  this->arr = tmp;

}

// Check if array is empty
// return true if array is empty
template <typename T>
bool ArrayClass<T>::empty() const
{
  return this->_size == 0;
}

// Resizes the array to fit exactly as many items
//   as are stored in the array
template <typename T>
void ArrayClass<T>::shrinkToFit()
{
  // empty array case, set to capacity to 1
  if (this->_size == 0)
  	this->_capacity = 1;
  // general case
  else
  	this->_capacity = this->_size;

  // create new temp arr to copy
  T* tmp = new T[this->_capacity];
  // copy all elements up to new capacity (and size)
  for (int i = 0; i < this->_capacity; i++)
  	tmp[i] = this->arr[i];
  // delete the old array and point it to the new resized one
  delete[] this->arr;
  this->arr = tmp;
}

//////////////////////////////
// element access functions //
//////////////////////////////

// Returns a reference to the element at position i
//   in the array.
// Throws an out_of_range exception if i is outside
//   the bounds of valid elements
template <typename T>
T& ArrayClass<T>::operator[](unsigned int i)
{
  if (this->_size == 0 || i >= this->_size || i < 0) {
    throw std::out_of_range("Out of range, operator[] called");
  }
  return this->arr[i];
}

// Returns a reference to the element at position i
//   in the array.
// Throws an out_of_range exception if i is outside
//   the bounds of valid elements
template <typename T>
T& ArrayClass<T>::at(unsigned int i)
{
  if (this->_size == 0 || i >= this->_size || i < 0) {
    throw std::out_of_range("Out of range, at() called");
  }
  return this->arr[i];
}

// Returns a reference to the first element in the array
// Calling this on an empty array throws out_of_range exception
template <typename T>
T& ArrayClass<T>::front()
{
  if (this->_size == 0)
    throw std::out_of_range("Out of range, front() called");
  return this->arr[0];
}

// Returns a reference to the last element in the array
// Calling this on an empty array throws out_of_range exception
template <typename T>
T& ArrayClass<T>::back()
{
  if (this->_size == 0)
    throw std::out_of_range("Out of range, back() called");
  return this->arr[this->_size - 1];
}

//////////////////////
// modify functions //
//////////////////////

// Add an element at the end
// If array is at capacity before adding, then
//   expand the array to double its capacity and
//   then add.
template <typename T>
void ArrayClass<T>::pushBack(const T& item)
{
  // if size has reached capacity
  if (this->_size >= this->_capacity) {
    this->expandArray(); 
  }
  // increment size, take size - 1 for grabbing last element of 0 indexed array
  this->arr[++this->_size - 1] = item; 
}

// Removes the last stored element in the array,
//   reducing container size by 1.
// No effect if called on an empty container
template <typename T>
void ArrayClass<T>::popBack()
{
  // empty check
  if (this->_size == 0)
  	return;
  // decrement size, previous back element should no longer be accessable
  this->_size--;
}

// Inserts an element before the element at specified position
// Expands the array if necessary
// Elements to the right of position (inclusive) must be shifted
// Throws out_of_range if position is > _size
// POST: item is at position, all elements formerly at position and beyond are shifted
template <typename T>
void ArrayClass<T>::insert(unsigned int position, const T& item)
{
  // check for invalid position
  if (position > this->_size)
  	throw std::out_of_range("insert() called with position > _size");
  // edge case for inserting at end of array
  if (position == this->_size) {
  	this->pushBack(item);
  	return;
  }
  // check for possible expansion
  this->_size++;
  if (this->_size > this->_capacity)
  	this->expandArray();

  // temp array pre-insert
  T* tmp = new T[this->_capacity];
  for (int i = 0; i < this->_size - 1; i++) {
  	tmp[i] = this->arr[i];
  }
  // copy items up to position
  for (int i = 0; i != position; i++) {
  	this->arr[i] = tmp[i];
  }
  // insert item at position
  this->arr[position] = item;
  for (int i = position + 1; i < this->_size; i++) {
  	// get all elements from temp array and shift
  	this->arr[i] = tmp[i - 1];
  }
  // free temp memory
  delete[] tmp;

}

// Removes an element from the array at specified position.
// Elements to the right of position will be shifted over to fill the gap
// Throws out_of_range if position is >= _size
template <typename T>
void ArrayClass<T>::erase(unsigned int position)
{
  if (position >= this->_size)
  	throw std::out_of_range("erase() called with position >= _size");
  for (int i = 0; i < this->_size; i++) {
  	// located position to erase
  	if (i == position) {
  		// shift all elements over to the left to fill the gap
  		for (; i < this->_size - 1; i++) {
  			this->arr[i] = this->arr[i + 1];
  		}
  	}
  }
  this->_size--;
}

// Reallocates stored items into a new array of the same size,
//   starting from specified position
// No effect if position is 0 or >= _size
// e.g. startFrom(3) on {1, 2, 3, 4, 5, 6, 7}
//   produces {4, 5, 6, 7, 1, 2, 3}
template <typename T>
void ArrayClass<T>::startFrom(unsigned int position)
{
  // check for bounds
  if (position == 0 || position >= this->_size)
    return;

  // create temporary arr to store all the data
  T* tmp = new T[this->_size];
  for (int i = 0; i < this->_size; i++) {
    tmp[i] = this->arr[i];
  }

  // var to keep track of shifted indices
  int newIndex = 0;
  // loop to grab all elements starting from position,
  // insert into front of array
  for (int i = position; i < this->_size; i++) {
    this->arr[newIndex] = tmp[i];
    newIndex++;
  }
  // loop to get all elements before position,
  // insert into rest of the array
  for (int i = 0; i < position; i++) {
    this->arr[newIndex] = tmp[i];
    newIndex++;
  }
  // free memory associated with temp array
  delete[] tmp;
}

//////////////////////
// helper functions //
//////////////////////

// helper method for deep copy
template <typename T>
void ArrayClass<T>::copyArray(const ArrayClass& ac)
{
	// update size and capacity
  	this->_size = ac._size;
  	this->_capacity = ac._capacity;
  	// create a temp array
	T* tmp = new T[ac._capacity];
	// copy all elements over
    for (int i = 0; i < ac.size(); i++)
      tmp[i] = ac.arr[i]; 
  	// delete the old array, point it to the new one
  	delete[] this->arr;
  	this->arr = tmp;
}

// helper method for expanding array
template <typename T>
void ArrayClass<T>::expandArray()
{
  this->_capacity *= EXPANSIONFACTOR;
  T* tmp = new T[this->_capacity];
  for (int i = 0; i < this->_size; i++) {
    tmp[i] = this->arr[i];
  }
  delete[] this->arr; 
  this->arr = tmp;
}

#endif