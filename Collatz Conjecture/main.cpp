/* Author: Chun-Yip Tang */
/* Date: January 10, 2017*/
#include <iostream>
#include <cmath>
#include <stdlib.h>
using namespace std;
/*
	This program is meant to take in 1 input of a constant whole number at runtime and then, using Collatz Conjecture, 
	see if, given the constraints, it will return to 1.
	
	The Collatz conjecture says that for any number postulated, if it is even, divide by 2; if it is odd
	multiply by 3 and add 1. Repeat indefinitely. The conjecture states that eventually, it will return 
	to 1.
*/
double odd(double num) {
	double result;
	result = (3 * num) + 1;
	return result;
}

double even(double num) {
	double result;
	result = num / 2;
}

int main(int argc, char **argv) {
	//inital setup
	int count = 0; //counts the number of calculations done to get to the answer.
	double num = atof(argv[1]); // gets the first value and puts it into variable num
	
	cout << "You entered " << argv[1] << endl; // just prints out the number so the user can confirm the input number
	
	while (num != 1) {
		if(fmod(num, 2) == 0) { // if even
			num = even(num);
		}
		else {				  // if odd
			num = odd(num);
		}
		count++;
	}
	
	//outputs how many calculations are done to achieve the answer
	cout << "Number of calculations " << count << endl;
	cout << "Final Number is " << num;
	
	
}