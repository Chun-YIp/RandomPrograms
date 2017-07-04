/* Author: Chun-Yip Tang */
/* Date: June 23, 2017*/
#include <iostream>
using namespace std;

/* 	This program is used to calculate the factorial of a number using 
	recursion. This number must be a valid integer.
*/

//basic factorial using recursion
int factorial(int num) {
	if (num <= 1)
		return 1;
	return num * factorial(num - 1);
}

int main() {
	int input; // The number we will be using to calculate the factorial
	int timesInput = 0; // value to change starting text.
	
	//This part is used to get input and re-prompt user if the input is not an
	//integer.
	while(true) {
		// The next few lines are used to prompt the user for input.
		if(timesInput != 0)
			cout << "Enter a number to calculate" << endl;
		else
			cout << "Enter another number please" << endl;
		
		cin >> input;
		
		//checks if the input is a valid integer. If not, the program will 
		//prompt the user to re-enter
		if(cin.fail())
			cout << "Entry is not a valid integer." <<
				"Please try again" << endl;
		else
			break;
	}
	
	// calls the factorial function with the user inputted number. Then prints
	//out the return
	cout << "\n\n" << factorial(input);
}