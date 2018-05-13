#include "linkedlist.h"

void LinkedList::copyList(const LinkedList& ll) {
	if (ll.front == NULL) {
		this->front = NULL;
		this->back = NULL;
	}
	else {
		// construct the new head node with a new Kebab object
		Kebab* kebabHead = new Kebab();
		kebabHead->buildKebab(ll.front->data->listIngredients());
		Node* firstNode = new Node(kebabHead);
		// set this front pointer to the kebab
		this->front = firstNode;
		Node* copy = this->front; // for traversing through this list
		Node* currLL = ll.front; // for traversing through ll
		currLL = currLL->next; // first element already copied
		this->length++;
		while (currLL != NULL) {
			// create new kebab object
			Kebab* kebabData = new Kebab();
			kebabData->buildKebab(currLL->data->listIngredients());
			// create new node
			copy->next = new Node(kebabData);
			// continue traversal for both lists, increment length
			currLL = currLL->next;
			copy = copy->next;
			this->length++;
		}
		this->back = copy;
	}
}

void LinkedList::deleteList() {
	Node* temp = this->front; 
	// empty list
	if (temp->next == NULL)
		return;
	// general case
	else {
		while (temp->next != NULL) {
			this->front = this->front->next;
			delete temp;
			temp = this->front;
		}
		delete this->back;
		this->front = NULL;
		this->back = NULL;
		this->length = 0;
	}
}

LinkedList::LinkedList() {
	this->length = 0;
	this->front = NULL;
	this->back = NULL;
}

LinkedList::LinkedList(const LinkedList& ll) {
	this->copyList(ll);
}

LinkedList::~LinkedList() {
	this->deleteList();
}

void LinkedList::insertFront(Kebab* item) {
	Node* temp = new Node(item);
	temp->next = front;
	this->front = temp; // back doesn't need to change since last element stays the same
	if (this->length == 0)
		this->back = temp;
	this->length++;
}

void LinkedList::insertBack(Kebab* item) {
	Node* insert = new Node(item);
	if (this->back == NULL) {
		this->back = insert;
	} else {
		back->next = insert;
		this->back = insert;
	}
	if (this->length == 0)
		this->front = insert;
	this->length++;
}

bool LinkedList::insertAt(Kebab* item, unsigned int p) {
	if (p >= this->length && p != 0) 
		return false;
	if (p == 0) {
		this->insertFront(item);
		return true;
	} else if (p == this->length - 1) {
		this->insertBack(item);
		return true;
	}

	Node* insert = new Node(item);
	Node* temp = front;

	// traverse through the list and arrive at position p
	for (unsigned int i = 0; i < p; i++) {
		temp = temp->next; 	// temp = position p
	}
	insert->next = temp; // inserted node points at the previous node at p
	temp = front; // reset the node for traversing
	// traverse through list to position p - 1
	for (unsigned int i = 0; i < p - 1; i++)
		temp = temp->next;
	temp->next = insert; // temp is now pointing to the inserted node
	this->length++;
	return true;
}

Kebab* LinkedList::removeAt(unsigned int p) {
	if (p >= this->length)
		return NULL;

	Node* temp = front;
	Kebab* ret; // to store Kebab object from deleted node
	if (this->length == 1) { // a single node will have both pointers removed
		ret = temp->data;
		temp->data = NULL;
		delete temp;
		this->length--;
		return ret;
	} else {
		if (p == 0) {
			ret = front->data;
			this->front = front->next;
			temp->data = NULL;
			delete temp;
			this->length--;
			return ret;
		}
		// traverse through the list and arrive at position p - 1
		for (unsigned int i = 0; i < p - 1; i++) {
			temp = temp->next;
		}
		// temp is holding node at p - 1 
		Node* toRemove = temp->next; // node to remove is at position p
		Node* toPointAt = toRemove->next; // node which the node (to remove) is pointing at
		temp->next = toPointAt; // position p - 1 now points at position p + 1
		ret = toRemove->data;
		if (p == this->length - 1) { // set back pointer to (p - 1)th node
			this->back = temp;
		}
		this->length--;
		toRemove->data = NULL;
		delete toRemove;
		return ret;
	}
}

unsigned int LinkedList::size() const {
	return this->length;
}

bool LinkedList::isEmpty() const {
	return (this->length == 0);
}

bool LinkedList::contains(Kebab& k) const {
	if (isEmpty())
		return false;
	Node* temp = front;
	while (temp->next != NULL) { // traverse through the list to the END
		if ((temp->data)->hasSameIngredients(k))
			return true;
		temp = temp->next;
	}
	return false;
}

Kebab* LinkedList::elementAt(unsigned int p) const {
	if (p >= this->length)
		return NULL;
	Node* temp = front;
	unsigned int counter = 0;
	while (temp->next != NULL && counter < p) {
		temp = temp->next;
		counter++;
	}
	// now temp points to node at position p
	Kebab* ret = temp->data;
	return ret;
}

LinkedList& LinkedList::operator=(const LinkedList& ll) {
	// guard from self-assignment
	if (&ll != this) {
		this->deleteList();
		this->copyList(ll);
	}
	return *this;
}
