// file:        stack.cpp
// author:      Kevin Chan
// date:        2017-10-21
// description: implementation of a stack class for CPSC 221 PA2

#ifdef _STACK_H_

// default constructor
template <typename T>
Stack<T>::Stack() {
	// default constructor for ArrayClass called - nothing here!
}

// copy constructor
template <typename T>
Stack<T>::Stack(const Stack& st) {
	this->ac = st.ac;
}

// assignment operator
template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& st) {
	// check for self-assignment
	if (&st != this)
		this->ac = st.ac;
	return *this;
}

///////////////
// accessors //
///////////////

// Return true if the stack contains no items
template <typename T>
bool Stack<T>::isEmpty() const {
	return ac.empty();
}

// Returns the number of items stored in the stack
template <typename T>
unsigned int Stack<T>::size() const {
	return ac.size();
}

// Return a reference to the top item of the stack
// Throws an out_of_range exception if the stack is empty
template <typename T>
T& Stack<T>::peek() {
	return this->ac.back();
}

//////////////
// mutators //
//////////////

// Pushes an item to the top of the stack
template <typename T>
void Stack<T>::push(const T item) {
	this->ac.pushBack(item);
}

// Removes and returns (a copy of) the top item of the stack
// Throws an out_of_range exception if the stack is empty
template <typename T>
T Stack<T>::pop() {
	T ret = this->ac.back();
	this->ac.popBack();
	return ret;
}

#endif