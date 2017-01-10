/* Author: Chun-Yip Tang */
/* Date: January 10, 2017*/
#include <iostream>
#include <cmath>
#include <stdlib.h>
using namespace std;
/*
	This program is meant to take in 1 input of a constant whole number and then, using Collatz Conjecture, 
	see if, given the constraints, it will return to 1.
*/
double odd(double num) {
	double result;
	result = 3 * num + 1;
	return result;
}

double even(double num) {
	double result;
	result = num / 2;
}

int main(int argc, char **argv) {
	//inital setup
	int timesDone = 0;
	int count = 0;
	double num;
	double curr = atof(argv[1]); // gets the first value and puts it into variable
	num	= curr; //actual variable to divide is set
	
	cout << argv[1] << "\n";
	while(timesDone < 1000){ // goes through 1000 numbers starting from first input and incrementing by 1
		while (num != 1) {
			if(fmod(num, 2) == 0) // if even
				num = even(num);
			else 				  // if odd
				num = odd(num);
			count++;
			cout << num << "\n";
		}
		cout << "Number of calculations " << count;
		//setup for the next number in the loop
		timesDone++;
		count = 0;
		curr++; //increases starting value
		num = curr;
	}
}