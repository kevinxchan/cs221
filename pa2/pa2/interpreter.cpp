#include "interpreter.h"

using namespace std;

///////////////////////
// PRIVATE FUNCTIONS //
///////////////////////

// executes an operator, returns a string of execution result
// most operators will return the empty string "", except for RQ, PRINT
// If an operator causes a container exception, throw the caught exception
std::string Interpreter::execOp(std::string optr) {
	int operand;
	string ret = ""; // return string
	// case 0: operand encountered; push to bin
	if (stringstream(optr) >> operand) {
		bin.push(operand);
		return "";
	}
	// case 1: # operator encountered
	if (optr == "#")
		return "";
	// case 2: print operator encountered
	if (optr == "PRINT") {
		while (hasMoreInstructions()) {
			ret += tube.dequeue();
		}
		return ret;
	}
	// case 3: RQ operator encountered
	if (optr == "RQ") {
		while (!bin.isEmpty()) {
			// place the ORIGINAL item into the sparebin
			sparebin.push(bin.peek());
			// enqueue a COPY of the item into the tube. must be converted to string
			string copy = toString(bin.pop());
			tube.enqueue(" " + copy);
			// ensure last operand does not have space following, else include space
			if (bin.isEmpty()) {
				ret += copy;
			}
			else {
				ret += copy + " ";
			}
		}
		while (!sparebin.isEmpty()) {
			// re-push ORIGINAL items into the bin from sparebin
			bin.push(sparebin.peek());
			// pop elements from sparebin
			sparebin.pop();
		}
		return ret;
	}
	// case 3: binary operator called
	if (optr == "+" || optr == "-" || optr == "*" || optr == "/" || optr == "^") {
		// right operand for operation is FIRST element popped from bin
		int rightOperand = bin.pop();
		// left operand for operation is SECOND element popped from bin		
		int leftOperand = bin.pop();
		string toEnqueue;

		// calculate left + right, change to string
		if (optr == "+")
			toEnqueue = " " + toString(leftOperand + rightOperand);
		// calculate left + right, change to string
		else if (optr == "-")
			toEnqueue = " " + toString(leftOperand - rightOperand);
		// calculate left * right, change to string
		else if (optr == "*")
			toEnqueue = " " + toString(leftOperand * rightOperand);
		// calculate left / right, change to string (int div)
		else if (optr == "/")
			toEnqueue = " " + toString(leftOperand / rightOperand);
		// calculate left ^ right, change to string 
		else if (optr == "^")
			toEnqueue = " " + toString(recpow(leftOperand, rightOperand));

		// enqueue back into the tube
		tube.enqueue(toEnqueue);
		return "";
	}

	return "";
}

// Exponentiation function calculates x^y
//   by repeated squaring (refer to HW2)
// You may implement this either iteratively or recursively
// PRE: y >= 0
int Interpreter::recpow(int x, int y) {
	if (y <= 0)
		return 1;
	int tmp = recpow(x, y/2);
	int ret = tmp * tmp;
	if (y % 2 == 0)
		return ret;
	else
		return x * ret;
}


//////////////////////
// PUBLIC FUNCTIONS //
//////////////////////

// default constructor
Interpreter::Interpreter() {
	// default ctor called for queue, stack
}

// copy constructor
Interpreter::Interpreter(const Interpreter& itpt) {
	tube = itpt.tube;
	bin = itpt.bin;
	sparebin = itpt.sparebin;
}

// assignment operator
Interpreter& Interpreter::operator=(const Interpreter& itpt) {
	// guard for self-assignment
	if (&itpt != this) {
		tube = itpt.tube;
		bin = itpt.bin;
		sparebin = itpt.sparebin;
	}
	return *this;
}

// Loads a single instruction into the tube
// Requires parsing the instruction into operators and operands
// If tube already contains items, the instruction is loaded
//   without clearing the tube contents
// This should inject a "#" operator at the end
void Interpreter::load(std::string instruction) {
	// sstream object to parse
	stringstream ss(instruction);
	// individual string instruction
	string token;
	// parse through the space delimited instruction
	while (ss >> token) {
		tube.enqueue(token);
	}
	tube.enqueue("#");
}

// Returns whether there are still items in the tube to be processed
bool Interpreter::hasMoreInstructions() {
	return !tube.isEmpty();
}

// Remove and execute next instruction
// i.e. until a #, empty tube, print, or other error encountered
// The output of any operator(s) will be returned
// If an attempt to execute an operator causes an exception,
//   throw the caught exception
std::string Interpreter::next() {
	string ret = "";
	string next = tube.dequeue();
	while (hasMoreInstructions()) {
		// execute next instruction, concatenate to string
		ret += execOp(next);
		// special cases
		if (next == "#") {
			return ret;
		}
		else if (next == "PRINT") {
			return ret;
		}
		next = tube.dequeue();
	}
	return ret;
}

// Execute remaining instructions
// The outputs of each instruction will be
// appended into a single string, separated by the
// newline character '\n'. The last instruction
// will NOT be followed by a newline.
std::string Interpreter::run() {
	string ret = next(); // return string
	while (hasMoreInstructions()) {
		ret += "\n" + next();
	}
	return ret;
}

// Clears the contents of all member containers (tube, bin, sparebin)
void Interpreter::clear() {
	while (!tube.isEmpty())
		tube.dequeue();
	while (!bin.isEmpty())
		bin.pop();
	while (!sparebin.isEmpty())
		sparebin.pop();
	
}
