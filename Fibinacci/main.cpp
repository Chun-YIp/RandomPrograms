#include <iostream>
using namespace std;
#define MAX 1000

int memo[MAX];

int fib(int n) {
	if(memo[n] != -1)
		return memo[n];
	if(n < 0)
		return 0;
	if(n <= 2)
		return 1;
	else{
		memo[n] = fib(n-1) + fib(n-2);
	}
	return memo[n];
}

int main() {
	int num;
	
	for (int i = 0; i < MAX; i++)
		memo[i] = -1;
	cout << "Please enter a number to compute";
	cin >> num;
	
	cout << fib(num);
	
	return 0;
}