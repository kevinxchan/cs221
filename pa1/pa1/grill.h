// File:        grill.h
// Author:      Geoff T, Jack S-J
// Date:        2017-09-18
// Description: Declaration of a grill class for CPSC 221 PA1
//              This file should not be modified

#ifndef _GRILL_H_
#define _GRILL_H_

#include "linkedlist.h"

class Grill
{
private:
  LinkedList rack;

public:
  // default constructor
  Grill();

  // Switches the kebabs at pos1 and pos2
  // Returns true if positions are valid and swap can be performed
  // Returns false if positions are invalid
  bool swap(unsigned int pos1, unsigned int pos2);

  // remove and return the kebab at a 1-indexed
  // position on the grill
  // return NULL if pos invalid
  Kebab* request(unsigned int pos);

  // remove and return the leftmost kebab matching
  // at least the ingredients of r, in any order
  // return NULL if no match found
  Kebab* request(Kebab& r);

  void addKebab(Kebab& n);

  // arrange in decreasing order of # of meat items
  void sortByMeat();

  // returns a vector containing the string representation of all
  //   kebabs on the grill
  std::vector<std::string> showKebabs() const;
};

#endif