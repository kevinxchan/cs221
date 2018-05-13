#ifdef _QUEUE_H_

template <typename T>
Queue<T>::Queue() {
	this->front = 0;
	this->_size = 0;
	// default constructor for ArrayClass called
}

// copy constructor
template <typename T>
Queue<T>::Queue(const Queue& qq) {
	this->ac = qq.ac;
	this->front = qq.front;
	this->_size = qq._size;
}

// assignment operator
template <typename T>
Queue<T>& Queue<T>::operator=(const Queue& qq) {
	// guard for self assignment
	if (&qq != this) {
		this->ac = qq.ac;
		this->front = qq.front;
		this->_size = qq._size;
	}
	return *this;
}

///////////////
// accessors //
///////////////

// Return true if the queue contains no items
template <typename T>
bool Queue<T>::isEmpty() const {
	return this->_size == 0;
}

// Returns the number of items stored in the queue
template <typename T>
unsigned int Queue<T>::size() const {
	return this->_size;
}

// Return a reference to the front item of the queue
// Throws an out_of_range exception if the queue is empty
template <typename T>
T& Queue<T>::peek() {
	return this->ac[this->front];
}

//////////////
// mutators //
//////////////

// Inserts an item to the back of the queue
template <typename T>
void Queue<T>::enqueue(const T item) {
	// case where there is space in the array container
	if (this->ac.size() < this->ac.capacity())
		this->ac.pushBack(item);
	// case where container size is full, but previous items have been dequeued
	if ((this->_size < this->ac.size()) && (this->ac.size() == this->ac.capacity())) {
		// get rear index for insertion, overwrite previously dequeued items
		int rear = (this->front + this->_size) % this->ac.capacity();
		// mod capacity
		this->ac[rear] = item;
	}
	// case where both queue and container is full; must resize container
	if (this->_size == this->ac.size()) {
		this->ac.startFrom(this->front);
		this->ac.pushBack(item);
		this->front = 0;
	}
	// increment size
	this->_size++;
}

// Removes and returns (a copy of) the front item of the queue
// Throws an out_of_range exception if the queue is empty
template <typename T>
T Queue<T>::dequeue() {
	// copy of front element
	T ret = this->ac[this->front];
	// mod capacity for circular queue
	this->front = (this->front + 1) % this->ac.capacity();
	this->_size--;
	return ret;
}

#endif