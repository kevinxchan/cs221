// file:        containertests.cpp
// author:      Geoff T
// date:        2017-10-07
// description: A few general tests for CPSC 221 PA2 container classes
//              You should add your own test cases!

#include <cstdlib>
#include <iostream>
#include <string>

#include "arrayclass.h"
#include "stack.h"
#include "queue.h"

using namespace std;

// forward function declarations
void arrayClassTests();
void stackTests();
void queueTests();

// program entry
int main()
{
  arrayClassTests();
  stackTests();
  queueTests();

  // Windows-specific, remove before distribution
#ifdef _WIN32
  system("pause");
#endif
  return 0;
}

void arrayClassTests()
{
  cout << "Entered arrayClassTests..." << endl;
  ArrayClass<int> ac1;
  ArrayClass<int> ac2(10);

  cout << "ac1 and ac2 created." << endl;
  cout << "ac1 size and capacity: " << ac1.size() << ", " << ac1.capacity() << endl;
  cout << "ac2 size and capacity: " << ac2.size() << ", " << ac2.capacity() << endl;

  if (ac1.empty() && ac2.empty())
    cout << "ac1 and ac2 are both empty" << endl;

  for (int i = 0; i < 7; i++)
  {
    ac1.pushBack(i + 10);
  }
  cout << "7 items pushed to ac1. New size and capacity: "
       << ac1.size() << ", " << ac1.capacity() << endl;
  cout << "ac1 contents: ";
  for (unsigned int i = 0; i < ac1.size(); i++)
  {
    cout << ac1[i] << " ";
  }
  cout << endl;
  
  cout << "Cycling ac1 items to start from index 3..." << endl;
  ac1.startFrom(3);
  cout << "ac1 contents: ";
  for (unsigned int i = 0; i < ac1.size(); i++)
  {
    cout << ac1[i] << " ";
  }
  cout << endl;

  ac2.pushBack(31);
  ac2.shrinkToFit();
  cout << "1 item pushed to ac2 and then ac2 shrunk. New size and capacity: "
       << ac2.size() << ", " << ac2.capacity() << endl;

  ac1.resize(3);
  cout << "ac1 resized down. New size and capacity: "
       << ac1.size() << ", " << ac1.capacity() << endl;

  cout << "ac1 contents: ";
  for (unsigned int i = 0; i < ac1.size(); i++)
  {
    cout << ac1[i] << " ";
  }
  cout << endl;

  cout << "ac2 contents: ";
  for (unsigned int i = 0; i < ac2.size(); i++)
  {
    cout << ac2.at(i) << " ";
  }
  cout << endl;

  ac1.popBack();
  cout << "popBack called on ac1. New size and capacity: "
       << ac1.size() << ", " << ac1.capacity() << endl;
  cout << "ac1 contents: ";
  for (unsigned int i = 0; i < ac1.size(); i++)
  {
    cout << ac1[i] << " ";
  }
  cout << endl;

  cout << "front of ac1: " << ac1.front() << endl;
  cout << "back of ac1: " << ac1.back() << endl;

  ac1.insert(0, 1);
  cout << "item inserted to ac1 at position 0. New size and capacity: "
       << ac1.size() << ", " << ac1.capacity() << endl;
  cout << "ac1 contents: ";
  for (unsigned int i = 0; i < ac1.size(); i++)
  {
    cout << ac1[i] << " ";
  }
  cout << endl;

  ac1.erase(1);
  cout << "item erased from ac1 at position 1. New size and capacity: "
    << ac1.size() << ", " << ac1.capacity() << endl;
  cout << "ac1 contents: ";
  for (unsigned int i = 0; i < ac1.size(); i++)
  {
    cout << ac1[i] << " ";
  }
  cout << endl;

  cout << "Assigning ac1 to ac2..." << endl;
  ac2 = ac1;
  cout << "ac2 contents: ";
  for (unsigned int i = 0; i < ac2.size(); i++)
  {
    cout << ac2.at(i) << " ";
  }
  cout << endl;

  cout << "Adding an item to ac2..." << endl;
  ac2.pushBack(303);
  cout << "ac1 size and capacity: " << ac1.size() << ", " << ac1.capacity() << endl;
  cout << "ac2 size and capacity: " << ac2.size() << ", " << ac2.capacity() << endl;
  cout << "ac1 contents: ";
  for (unsigned int i = 0; i < ac1.size(); i++)
  {
    cout << ac1[i] << " ";
  }
  cout << endl;

  cout << "ac2 contents: ";
  for (unsigned int i = 0; i < ac2.size(); i++)
  {
    cout << ac2.at(i) << " ";
  }
  cout << endl;

  ArrayClass<int> ac3;
  cout << "ArrayClass ac3 created. Attempting to call [], at, front, back..." << endl;
  try
  {
    cout << ac3[0];
  }
  catch (out_of_range e)
  {
    cout << "caught exception - ";
    cout << e.what() << endl;
  }
  try
  {
    cout << ac3.at(0);
  }
  catch (out_of_range e)
  {
    cout << "caught exception - ";
    cout << e.what() << endl;
  }
  try
  {
    cout << ac3.front();
  }
  catch (out_of_range e)
  {
    cout << "caught exception - ";
    cout << e.what() << endl;
  }
  try
  {
    cout << ac3.back();
  }
  catch (out_of_range e)
  {
    cout << "caught exception - ";
    cout << e.what() << endl;
  }

  cout << "Exiting arrayClassTests...\n" << endl;
}

void stackTests()
{
  cout << "Entered stackTests..." << endl;

  Stack<int> st1;
  Stack<int> st2;
  
  cout << "Stacks st1 and st2 created. Pushing 5 items to st1 and 3 items to st2..." << endl;
  st1.push(3);
  st1.push(4);
  st1.push(5);
  st1.push(6);
  st1.push(7);

  st2.push(11);
  st2.push(12);
  st2.push(13);

  cout << "Top of st1: " << st1.peek() << endl;
  cout << "Top of st2: " << st2.peek() << endl;

  cout << "Popping and printing all items from st1: ";
  while (!st1.isEmpty())
  {
    cout << st1.pop() << " ";
  }
  cout << endl;

  cout << "Assigning st2 to st1..." << endl;
  st1 = st2;
  cout << "Top of st1: " << st1.peek() << endl;

  Stack<int> st3;
  cout << "Stack st3 created. Attempting to call peek, pop..." << endl;
  try
  {
    cout << st3.peek();
  }
  catch (out_of_range e)
  {
    cout << "caught exception - ";
    cout << e.what() << endl;
  }
  try
  {
    cout << st3.pop();
  }
  catch (out_of_range e)
  {
    cout << "caught exception - ";
    cout << e.what() << endl;
  }

  cout << "Exiting stackTests...\n" << endl;
}

void queueTests()
{
  cout << "Entered queueTests..." << endl;

  Queue<string> q1;
  Queue<string> q2;

  cout << "Queues q1 and q2 created. Enqueueing 3 items to q1, "
    << "then dequeueing 2 items from q1, and enqueueing 5 more items to q1..." << endl;
  
  q1.enqueue("1");
  q1.enqueue("2");
  q1.enqueue("3");
  cout << "Dequeued items: " << q1.dequeue();
  cout << ", " << q1.dequeue() << endl;
  q1.enqueue("4");
  q1.enqueue("5");
  q1.enqueue("6");
  q1.enqueue("7");
  q1.enqueue("8");

  cout << "Enqueuing 3 items to q2..." << endl;
  q2.enqueue("11");
  q2.enqueue("12");
  q2.enqueue("13");

  cout << "q1 size: " << q1.size() << endl;
  cout << "Dequeuing all q1 contents: ";
  while (!q1.isEmpty())
  {
    cout << q1.dequeue() << " ";
  }
  cout << endl;

  cout << "q2 size: " << q2.size() << endl;
  cout << "Front of q2: " << q2.peek() << endl;

  cout << "Enqueueing 4 items to q1..." << endl;
  q1.enqueue("1");
  q1.enqueue("2");
  q1.enqueue("3");
  q1.enqueue("4");

  cout << "Assigning q1 to q2..." << endl;
  q2 = q1;

  cout << "q2 size: " << q2.size() << endl;
  cout << "Front of q2: " << q2.peek() << endl;

  cout << "Dequeueing 3 items from q2: ";
  cout << q2.dequeue() << " ";
  cout << q2.dequeue() << " ";
  cout << q2.dequeue() << endl;

  cout << "q1 size: " << q1.size() << endl;
  cout << "Front of q1: " << q1.peek() << endl;

  cout << "q2 size: " << q2.size() << endl;
  cout << "Front of q2: " << q2.peek() << endl;

  Queue<string> q3;
  cout << "Queue q3 created. Attempting to call peek, dequeue..." << endl;
  try
  {
    cout << q3.peek();
  }
  catch (out_of_range e)
  {
    cout << "caught exception - ";
    cout << e.what() << endl;
  }
  try
  {
    cout << q3.dequeue();
  }
  catch (out_of_range e)
  {
    cout << "caught exception - ";
    cout << e.what() << endl;
  }

  cout << "Exiting queueTests...\n" << endl;
}