#include <iostream>
using namespace std;

int factorial(int num) {
	if (num <= 1)
		return 1;
	return num * factorial(num - 1);
}

int main() {
	int input;
	
	while(true) {
		cout << "Enter a number to calculate";
		if(cin >> input)
			break;
	}
	
	cout << "\n\n" << factorial(input);
}