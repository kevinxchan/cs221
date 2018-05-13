// file:        interpretertest.cpp
// author:      Geoff T
// date:        2017-10-13
// description: A few general tests for CPSC 221 PA2 Interpreter class
//              You should add your own test cases!

#include <cstdlib>
#include <iostream>

#include "interpreter.h"

using namespace std;

// forward function declarations
void runScriptedTest();
void runInteractiveTest();
void displayMenu();
void handleQueryLoad(Interpreter& it);
void handleQueryRunOne(Interpreter& it);
void handleQueryRunAll(Interpreter& it);
void handleQueryClear(Interpreter& it);

// program entry
int main()
{
  runScriptedTest();
  runInteractiveTest();

  // Windows-specific, remove before distribution
#ifdef _WIN32
  system("pause");
#endif
  return 0;
}

// The expected output from this short program is:
// File loaded.
//
// 2
//
// # 3 2 9 - 6
void runScriptedTest()
{
  Interpreter intr;
  //intr.load("2 1 +");
  //intr.load("2 RQ");
  //intr.load("7 + 30 -5");
  //intr.load("/ PRINT");
  intr.load("12 3 2 ^ -6 RQ /");
  intr.load("4 2 RQ");
  intr.load("* PRINT");
  cout << "Program loaded." << endl;
  string output;
  while (intr.hasMoreInstructions())
  {
    output = intr.next();
    cout << output << endl;
  }
}

void runInteractiveTest()
{
  Interpreter intr;

  cout << "Interactive PA2 function started. Have a lot of fun..." << endl;

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
      case 1: // load an instruction
        handleQueryLoad(intr);
        break;
      case 2: // run one instruction
        handleQueryRunOne(intr);
        break;
      case 3: // run all instructions
        handleQueryRunAll(intr);
        break;
      case 4: // clear the interpreter state
        handleQueryClear(intr);
        break;
      case 8: // end
        cout << "Exiting postfixer-thingy. Good-bye..." << endl;
        break;
      default: // invalid option
        cout << "Invalid choice." << endl;
        break;
    }
  }
}

void displayMenu()
{
  cout << "**************************************\n"
    << "* Welcome to Postfixer-thingy terminal  *\n"
    << "* What would you like to do?            *\n"
    << "*                                       *\n"
    << "* Options:                              *\n"
    << "* 1. Load an instruction                *\n"
    << "* 2. Run one instruction                *\n"
    << "* 3. Run all instructions               *\n"
    << "* 4. Clear the interpreter state        *\n"
    << "*                                       *\n"
    << "* 8. End                                *\n"
    << "*****************************************" << endl;
  cout << "Please enter your choice: ";
}

void handleQueryLoad(Interpreter& it)
{
  string inst;
  cout << "Enter your properly-formatted instruction to load: ";
  getline(cin, inst);
  it.load(inst);
}

void handleQueryRunOne(Interpreter& it)
{
  if (it.hasMoreInstructions())
  {
    string result = it.next();
    cout << "Instruction output: " << result << endl;
  }
  else
  {
    cout << "Interpreter is empty." << endl;
  }
}

void handleQueryRunAll(Interpreter& it)
{
  if (it.hasMoreInstructions())
  {
    string result = it.run();
    cout << "Instruction output:\n" << result << endl;
  }
  else
  {
    cout << "Interpreter is empty." << endl;
  }
}

void handleQueryClear(Interpreter& it)
{
  it.clear();
  cout << "Interpreter state cleared." << endl;
}