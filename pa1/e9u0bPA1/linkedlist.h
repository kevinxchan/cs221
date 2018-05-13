// File:        linkedlist.h
// Author:      Geoff T, Jack S-J
// Date:        2017-09-18
// Description: Declaration of a singly-linked list class for CPSC 221 PA1
//              This file should not be modified

#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <cstdlib>

#include "kebab.h"

// LinkedList class definition
class LinkedList
{
private:
  // Node class used in LinkedList
  class Node
  {
    public:
      Kebab* data;
      Node* next;

      // default constructor
      Node(Kebab* value)
      {
        data = value;
        next = NULL;
      }

      // destructor
      ~Node()
      {
        delete data;
      }
  };

  // LinkedList private members
  unsigned int length; // number of items stored in list
  Node* front; // references to the front
  Node* back;  //  and back of the list

  // helper function for deep copy
  // Used by copy constructor and operator=
  // should create new Kebab objects
  void copyList(const LinkedList& ll);

  // helper function for deep delete
  // Used by destructor and copy/assignment
  // Deallocates Nodes and the Kebabs inside
  void deleteList();

public:
  // default constructor
  LinkedList();

  // copy constructor, performs deep copy of list elements
  LinkedList(const LinkedList& ll);

  // destructor
  ~LinkedList();

  // MUTATORS

  // Inserts an item at the front of the list
  // POST:  List contains item at position 0
  // PARAM: item = item to be inserted
  void insertFront(Kebab* item);

  // Inserts an item at the back of the list
  // POST:  List contains item at back
  // PARAM: item = item to be inserted
  void insertBack(Kebab* item);

  // Inserts an item in position p (0-indexed)
  // Returns false for invalid index
  // PRE:   0 <= p <= size
  // POST:  List contains item at position p
  // PARAM: item = item to be inserted, p = position where item will be inserted
  bool insertAt(Kebab* item, unsigned int p);

  // Removes and returns an item from position p (0-indexed)
  // Return NULL if index is invalid
  // PRE:   0 <= p < size
  // POST:  Item is removed from list.
  //        Node is deallocated but Kebab should in memory
  //        Thus set data to NULL before deleting
  // PARAM: p = position from where item will be removed
  Kebab* removeAt(unsigned int p);

  // ACCESSORS

  // Returns size of list
  unsigned int size() const;

  // Returns whether the list is empty
  bool isEmpty() const;

  // Returns existence of a Kebab that has at least
  //   all the same ingredients as k, in any order
  //   i.e. the list has a Kebab whose ingredients
  //   are a super-multiset of k's ingredients
  bool contains(Kebab& k) const;

  // Returns item at index (0-indexed)
  // Returns NULL if index is invalid
  Kebab* elementAt(unsigned int p) const;

  // OVERLOADED OPERATORS

  // overloaded assignment operator
  // must work in the following cases:
  // list2 = list1 -> general case
  // list2 = list2 -> should do nothing
  LinkedList& operator=(const LinkedList& ll);
};

#endif
