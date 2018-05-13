// File:        kebab.h
// Author:      Geoff T, Jack S-J
// Date:        2017-09-18
// Description: Declaration of a kebab class for CPSC 221 PA1
//              This file should not be modified

#ifndef _KEBAB_H_
#define _KEBAB_H_

#define SKEWER_SIZE 8 // maximum number of items on a skewer
#define NUM_INGS 5    // number of different types of ingredients

#include <vector>
#include <string>

// Kebab class definition
class Kebab
{
private:
  //LinkedList skewer;
  const unsigned int maxlength = SKEWER_SIZE;
  std::vector<char> skewer;

  // checks whether item is one of the five allowable ingredients
  // 'b' = beef, 't' = tomato, 'm' = mushroom, 'p' = pepper, 's' = squash
  // item may be upper or lower case
  bool isValidIngredient(char item)
  {
    return (item == 'b' || item == 'B' ||
            item == 't' || item == 'T' ||
            item == 'm' || item == 'M' ||
            item == 'p' || item == 'P' ||
            item == 's' || item == 'S');
  }

public:
  // default constructor
  Kebab();

  // Adds item to the pointy end of the skewer
  //   and returns true if skewer has space to add
  //   and item is a valid ingredient
  // Returns false if skewer is full or ingredient is invalid
  bool addIngredient(char item);

  // Adds the ingredients specified by s using addIngredient
  //   up to the capacity of the skewer
  void buildKebab(std::string s);

  // returns the number of meat items on this kebab
  unsigned int numMeats() const;

  // Returns true iff this kebab contains at least the same collection
  // of ingredients as k, in any order
  // Note that this kebab may contain more total ingredients than k,
  // but will return true as long as this kebab's ingredients is
  // a super-multiset of k's ingredients
  bool hasSameIngredients(Kebab& k) const;

  // Returns a string representing the ingredients on this kebab
  //   in the order in which they are skewered
  std::string listIngredients() const;
};

#endif