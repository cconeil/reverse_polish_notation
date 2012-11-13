using namespace std;
#include <iostream>
#include <vector>
#include <cmath>

// This function takes an input as RPN notation and outputs what it evaluates to.
// It expects the input to be proper RPN notation (for the most part)
// This was coded during and after an interview with Square on 10/26/12
// SOME OUTPUT EXAMPLES: 4 1 + = 5
//                       4 8 \* = 32
//                       4 5 4 + - = (5-4) + 4 = 5
//                       4 2 5 5 5 5 / + - + - = (4/(2+(5-(5+(5-5))))) = 2
// 					     1 1 + 3 - 8 \* 6 + = -2
// NOTICE:---------------------------------------------------------------
// NOTICE: the operators we can take in as input are: +, -, /, x, '*', \*
// NOTICE: (I don't know how to excape * in the arguments)
// NOTICE: *Debugging is left in for recruiter's purposes
// NOTICE:---------------------------------------------------------------
// written with love by:
// Chris O'Neil

// ERROR CHECKING--------
/*
CHECK 		  1. Support for negative numbers as arguments
CHECK		  2. Checking for extra operators
CHECK         3. Checking for extra operands (you might already have this one)
CHECK         4. Checking for invalid input (e.g. ./rpn @)
CHECK         5. Checking for division by 0
CHECK         6. Support for unary plus (e.g. ./rpn 3 + should output 3)
CHECK		  7. Support for unary minus (e.g. ./rpn 3 - should output -3)
CHECK		  8. Declaring your operators in only one place, i.e. I should be able to add ^ to do power 
   				 (e.g. ./rpn 2 3 ^ should output 8) without having to 
   				 change operator checks in multiple places
*/
// ----------------------



bool isInt(char *num);
// REQURIES: an array of characters that are numbers
// EFFECTS:  returns true if the array is full of digits, therefore making it an integer

bool isOp(char *op);
// REQUIRES: an array of characters that are operators.  each operator can only be one char
// EFFECTS:  returns true if this is not a number and it is a single character array.  The 
//			 check for being a legal operator will be done in 



int operation(int x, int y, char op);
// REQUIRES: this takes in two ints and a char.  the two ints are the operands, and the char is an operator
//           that is a single character.  This function will only work for operators that are defined within
//           it.  All edits to operations that we should include will be here.  Anything else will be classified
//           as an undefined operator.
// EFFECTS:  returns value given by two operands and a LEGAL operator.


int main(int argc, char* argv[])
// REQUIRES: this function requires inputs (as arguments) from the terminal.  This function is only
// 			 made to take in ints and the designated operators.  It then evaluates the expression.
// EFFECTS:  Returns the value of the expression, given that the expression is valid.
{
	vector <int> operands; // start by declaring our input vector
	int add_to_end;

	for(int i = 1; i < argc; i++)
	{
		// Check if we are using doing a unary operation such as:
		// 6 - = -6
		// 6 + = 6
		if (argc == 3)
		{
			/* // uncomment for debugging purposes
			cout << "argc == 3" << endl;
			cout << "argv[i]: " << argv[i] << endl;
			cout << "argv[i+1]: " << argv[i+1] << endl;
			*/
			if (isInt(argv[i]) && isOp(argv[i+1]))
			{
			int add_to_end = operation(0, atoi(argv[i]), *argv[i+1]);
			//cout << "This is what we are going to output if argc == 3: " << add_to_end << endl;
			// ^^^ uncomment for debugging purposes ^^^
			operands.push_back(add_to_end);
			} else {
				cerr << "Oops! Ther is an error in your unary operation." << endl;
			}
			break;

		// Normal case
		} else if (isInt(argv[i]))
		{
			// here we need to add our element to the FRONT of the vector
			// so we have to reverse it, add it to the end, and then reverse
			// it again so the element that we added to the end of the
			// reversed list is at the beginning of the new list.
			reverse(operands.begin(), operands.end());
			operands.push_back(atoi(argv[i]));
			reverse(operands.begin(), operands.end());

			/* // uncomment for debugging purposes
			cout << "The size of the vector is: " << operands.size() << endl;
			cout << "The first element of the vector is: " << operands.at(0) << endl;
			cout << "The last element of the vector is: " << operands.at(operands.size()-1) << endl;
			*/
		
		// If it's an operand
		} else {
			if (isOp(argv[i]))
			{
				// take the last two elemnts and delete them from our vector
				int first = operands.back();
				operands.pop_back();
				int second = operands.back();
				operands.pop_back();

				/* // uncomment for debugging purposes
				cout << "First element taken: " << first << endl;
				cout << "Second element taken: " << second << endl;
				cout << "The size after taking 2 is: " << operands.size() << endl;
				*/

				char operate = *argv[i]; // this is our current operator

				add_to_end = operation(first, second, operate);
				operands.push_back(add_to_end);

			} else {
				cerr << "You have too many operators" << endl;
				exit(1);
			}
		} // end else
	} // end for


	if (operands.back() != operands.front())
	{
		cerr << "Oops! Something is wrong!" << endl;
		exit(1);
	}

	cout << "The RPN expression evaluates to: " << operands.back() << endl;
	
	return 0;
}


bool isInt(char *num)
{
	while(*num)
	{
		if (*num == '-')
		{
			num++;
			if (*num >= '0' && *num <= '9')
			{
				return true;
			} else {
				return false; // this is just a subtraction sign.
			}
		}
		else if (*num < '0' || *num >'9')
		{
			return false;
		}
	num++;
	}
	return true;
}


bool isOp(char *op)
{
	if (strlen(op) > 1)
	{
		return false;
	}
	if (*op >= '0' && *op <= '9')
	{
		return false;
	}
	return true;
}


int operation(int x, int y, char op)
{
	//cout << "operator: " <<  op << endl; // uncomment for debugging
	if (op == '+')
	{
		//cout << "addition!" << endl; // uncomment for debugging purposes
		return x + y;
	} else if (op == '*' || op == 'x')
	{
		//cout << "multiplication!" << endl; // uncomment for debugging purposes
		return x * y;
	} else if (op == '/')
	{
		if (y == 0)
		{
			cerr << "You can't divide by zero." << endl;
			exit(1);
		} else {
		//cout << "division!" << endl; // uncomment for debugging purposes
		return x / y;
		}
	} else if (op == '-')
	{
		//cout << "subtraction!" << endl; // uncomment for debugging purposes
		return x-y;
	}  else if (op == '^')
	{
		//cout << "exponent!" << endl; // uncomment for debugging purposes
		return pow(static_cast<double>(x),y);
	} else if (op == '%')
	{
		//cout << "modulus!" << endl; // uncomment for debugging purposes
		return x % y;
	} else {
		cerr << "There is an error in your sign." << endl;
		exit(1);
	}
}