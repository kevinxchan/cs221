// File:        main.cpp
// Author:      Geoff T
// Date:        2017-09-18
// Description: Test driver for CPSC 221 PA1
//              Only basic cases are included. You are responsible
//              for adding your own code to thoroughly test all functions of the
//              classes implemented in this assignment.

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#include "kebab.h"
#include "linkedlist.h"
#include "grill.h"

using namespace std;

// forward function declarations
void runScriptedTests();
void runInteractiveTest();
void displayMenu();
void handleQueryShowGrill(Grill& grill);
void handleQueryBuyX(Grill& grill);
void handleQueryBuyList(Grill& grill);
void handleQueryNewKebab(Grill& grill);
void handleQuerySwap(Grill& grill);
void handleQuerySort(Grill& grill);

int main()
{
  //runScriptedTests();
  runInteractiveTest();

  return 0;
}

void runScriptedTests()
{
  // Add your testing code here
  // You are expected to instantiate Kebab, LinkedList, and Grill objects
  // and to thoroughly test all of your implemented functions

  // !!! KEBAB TESTS
  /*
  testKebab->buildKebab("");

  cout << "EXPECTED # INGREDIENTS: " << 0 << endl;
  cout << "ACTUAL: " << testKebab->listIngredients().size() << endl;
  cout << endl;
  */

  /*
  testKebab->buildKebab("BBBBBBBBBBBBBBBBBB");
  cout << "EXPECTED # INGREDIENTS: " << 8 << endl;
  cout << "ACTUAL: " << testKebab->listIngredients().size() << endl;
  cout << endl;
  */

  /*
  testKebab->buildKebab("MmBbt");

  cout << "EXPECTED # INGREDIENTS: " << 5 << endl;
  cout << "ACTUAL: " << testKebab->listIngredients().size() << endl;
  cout << endl;

  cout << "EXPECTED # MEATS: " << 2 << endl;
  cout << "ACTUAL: " << testKebab->numMeats() << endl;
  cout << endl;
  */

  /*
  testKebab->buildKebab("hBs3 Px/=mMt");

  cout << "EXPECTED STRING: " << "BsPmMt" << endl;
  cout << "ACTUAL STRING: " << testKebab->listIngredients() << endl;
  cout << endl;
  cout << "EXPECTED # MEATS: " << 2 << endl;
  cout << "ACTUAL: " << testKebab->numMeats() << endl;
  cout << endl;
  */

  /*
  k->buildKebab("bm");
  cout << "EXPECTED TRUE CASE" << endl;
  cout << "ACTUAL: " << testKebab->hasSameIngredients(*k) << endl;
  */

  /*
  k->buildKebab("bmM");
  cout << "EXPECTED TRUE CASE" << endl;
  cout << "ACTUAL: " << testKebab->hasSameIngredients(*k) << endl;
  */

  /*
  k->buildKebab("bmMtt");
  cout << "EXPECTED FALSE CASE" << endl;
  cout << "ACTUAL: " << testKebab->hasSameIngredients(*k) << endl;
  */

  /*
  k->buildKebab("BMPST");
  Kebab* t = new Kebab();
  t->buildKebab("bST");
  cout << t->hasSameIngredients(*k) << endl;
  cout << k->hasSameIngredients(*t) << endl;
  */
  // !!! END KEBAB TESTS

  // Kebab* node0 = new Kebab();
  // Kebab* node1 = new Kebab();
  // Kebab* node2 = new Kebab();
  // Kebab* nodeInsert = new Kebab();
  // Kebab* node4 = new Kebab();
  // Kebab* nodeDNE = new Kebab();

  // node0->buildKebab("BBPPSTTm");
  // node1->buildKebab("pm");
  // node2->buildKebab("pmm");
  // nodeInsert->buildKebab("sSt");
  // node4->buildKebab("TMS");

  // nodeDNE->buildKebab("stt");

  // LinkedList* ll = new LinkedList();

  // ll->insertFront(node0);
  // ll->insertBack(node1);
  // ll->insertBack(node2);
  // ll->insertBack(nodeInsert);
  // ll->insertBack(node4);

  // Kebab* copyOfNode0 = new Kebab();
  // copyOfNode0->buildKebab("sT");
  // //cout << node0->hasSameIngredients(*nodeDNE) << endl;
  // cout << ll->contains(*copyOfNode0) << endl;

  // cout << "LL ORIGINAL SIZE: " << ll->size() << endl;
  // for (int i = 0; i < ll->size(); i++) 
  //   cout << "NODE " << i << " ING: " << ll->elementAt(i)->listIngredients() << endl;

  //for (int i = 0; i < ll->size(); i++) 
   // cout << "NODE " << i << " ING FOR LL: " << ll->elementAt(i)->listIngredients() << endl;

  //copy->insertBack(nodeDNE);
  // cout << copy->size() << endl;
  // cout << ll->size() << endl;
  // copy = ll;
  // cout << "COPY SIZE: " << copy->size() << endl;
  // for (int i = 0; i < copy->size(); i++) 
  //   cout << "NODE " << i << " ING FOR COPY: " << copy->elementAt(i)->listIngredients() << endl;


  // cout << "LL ORIGINAL SIZE AFTER COPY: " << ll->size() << endl;
  // cout << "COPY SIZE: " << copy->size() << endl;
  // for (int i = 0; i < copy->size(); i++) 
  //   cout << "NODE " << i << " ING: " << copy->elementAt(i)->listIngredients() << endl;

  // copy->insertBack(nodeDNE);
  // for (int i = 0; i < ll->size(); i++) 
  //   cout << "NODE " << i << " ING FOR LL: " << copy->elementAt(i)->listIngredients() << endl;

  // for (int i = 0; i < copy->size(); i++) 
  //   cout << "NODE " << i << " ING FOR COPY: " << copy->elementAt(i)->listIngredients() << endl;

  // LinkedList lla; 
  // lla.insertFront(new Kebab());
  // lla.elementAt(0)->addIngredient('b');
  // lla.insertAt(new Kebab(), 0);
  // lla.elementAt(0)->addIngredient('m');
  // if (lla.elementAt(1)->listIngredients().compare("b") == 0)
  //   cout << "Yay" << endl;
  // else
  //   cout << "Uh-oh" << endl;

  // Grill test;
  // test.addKebab(*node0);
  // vector<string> v = test.showKebabs();
  //cout << v.size() << endl;
}

void runInteractiveTest()
{
  // create a Grill and populate it with some Kebabs
  Grill g;
  Kebab* freshkebab;
  freshkebab = new Kebab();
  freshkebab->buildKebab("TMTBPP");
  g.addKebab(*freshkebab);
  freshkebab = new Kebab();
  freshkebab->buildKebab("B 3%#SN,M[PM TBSB54M,ZDROB8RTZ3 564 /][98Z3");
  g.addKebab(*freshkebab);
  freshkebab = new Kebab();
  freshkebab->buildKebab("BMB");
  g.addKebab(*freshkebab);

  string inputchoice = "";
  int choice = 0;

  while (choice != 8)
  {
    displayMenu();
    // get the menu choice from standard input
    getline(cin, inputchoice);
    choice = atoi(inputchoice.c_str());

    switch (choice)
    {
    case 1: // See the kebabs
      handleQueryShowGrill(g);
      break;
    case 2: // Buy a kebab by pointing
      handleQueryBuyX(g);
      break;
    case 3: // Buy a kebab by listing ingredients
      handleQueryBuyList(g);
      break;
    case 4: // Make a new kebab
      handleQueryNewKebab(g);
      break;
    case 5: // Swap two kebabs on the grill
      handleQuerySwap(g);
      break;
    case 6: // Descending sort the kebabs by meat amount
      handleQuerySort(g);
      break;
    case 8: // End
      cout << "Thank you, come again!" << endl;
      break;
    default: // invalid option
      cout << "Invalid choice." << endl;
      break;
    }
  }
}

// prints the options menu to screen
void displayMenu()
{
  cout << "*****************************************\n"
       << "* Welcome to Speedy Kebab terminal      *\n"
       << "* What would you like to do?            *\n"
       << "*                                       *\n"
       << "* Customer operations:                  *\n"
       << "* 1. See the kebabs on the grill        *\n"
       << "* 2. Buy a kebab by number              *\n"
       << "* 3. Buy a kebab by listing ingredients *\n"
       << "*                                       *\n"
       << "* Staff operations:                     *\n"
       << "* 4. Make a new kebab                   *\n"
       << "* 5. Swap two kebabs                    *\n"
       << "* 6. Sort by meat amounts               *\n"
       << "*                                       *\n"
       << "* 8. End                                *\n"
       << "*****************************************" << endl;
  cout << "Please enter your choice: ";
}

void handleQueryShowGrill(Grill& grill)
{
  vector<string> kebabs = grill.showKebabs(); // seg fault
  int numkebabs = kebabs.size();
  // pad all kebab strings with " " to make them SKEWER_SIZE
  for (int i = 0; i < numkebabs; i++)
  {
    if (kebabs[i].length() < SKEWER_SIZE)
    {
      while (kebabs[i].length() < SKEWER_SIZE)
        kebabs[i] = kebabs[i] + " ";
    }
    cout << i + 1 << "\t";
  }
  cout << endl;
  for (int i = 0; i < numkebabs; i++)
    cout << "~~~\t";
  cout << endl;
  for (int chars = 0; chars < SKEWER_SIZE; chars++)
  {
    for (int k = 0; k < numkebabs; k++)
    {
      cout << kebabs[k][chars] << "\t";
    }
    cout << endl;
  }
}

void handleQueryBuyX(Grill& grill)
{
  string inputchoice = "";
  int choice = 0;
  cout << "Enter the number of the kebab: ";
  getline(cin, inputchoice);
  choice = atoi(inputchoice.c_str());
  Kebab* purchased = grill.request((unsigned int)choice);
  if (purchased != NULL)
    cout << "Thank you, enjoy!\n" << endl;
  else
    cout << "Sorry, I cannot help you with that.\n" << endl;
  delete purchased;
}

void handleQueryBuyList(Grill& grill)
{
  string wanted;
  cout << "Enter the first character of each ingredient you want: ";
  getline(cin, wanted);
  Kebab wantedkebab;
  wantedkebab.buildKebab(wanted);
  Kebab* purchased = grill.request(wantedkebab);
  if (purchased != NULL)
    cout << "Thank you, enjoy!\n" << endl;
  else
    cout << "Sorry, I cannot help you with that.\n" << endl;
  delete purchased;
}

void handleQueryNewKebab(Grill& grill)
{
  string ilist;
  cout << "Enter the first character of each ingredient to use: ";
  getline(cin, ilist);
  Kebab* freshkebab = new Kebab();
  freshkebab->buildKebab(ilist);
  grill.addKebab(*freshkebab);
  cout << "A fresh kebab is on the grill!\n" << endl;
}

void handleQuerySwap(Grill& grill)
{
  string inputchoice = "";
  int k1 = 0;
  cout << "Enter the number of the first kebab: ";
  getline(cin, inputchoice);
  k1 = atoi(inputchoice.c_str());
  int k2 = 0;
  cout << "Enter the number of the second kebab: ";
  getline(cin, inputchoice);
  k2 = atoi(inputchoice.c_str());
  if (grill.swap((unsigned int)k1, (unsigned int)k2))
    cout << "Kebabs swapped.\n" << endl;
  else
    cout << "Sorry, you cannot do that.\n" << endl;
}

void handleQuerySort(Grill& grill)
{
  grill.sortByMeat();
  cout << "More meat on the left!\n" << endl;
}
