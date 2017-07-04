#include <stdio.h>
#include <stdlib.h>

void printArr(int arr[]) {
	for(int i = 0; i < 10; i++) {
		for(int j = 0; j < 10; j++) {
			printf("%d\t", arr[(i*10)+j]);
		}
		printf("\n");
	}
}

int main() {
	//initialize an array of 100 integers
	int arr[100], arr2[100];
	int arr3[100][2];
	int sum;
	int avg;
	int highestDistribution = 0, hDnum;
	
	//gives a random number to each of the elements in arr
	//finds the sum and then the average of the numbers
	for(int i = 0; i < 99; i++) {
		arr[i] = rand() % 100 + 1;
		sum += arr[i];
	}
	avg = sum / 100;
	
	//finds the distance between each random value in arr and assigns it to arr2
	arr2[0] = 0;
	for(int i = 1; i < 99; i++) {
		arr2[i] = arr[i] - arr[i - 1];
	}
	
	//finds which number came out the most
	for(int i = 0; i < 99; i++) {
		arr3[i][1] = 0;
	}
	for(int i = 0; i < 99; i++) {
		int temp = arr2[i];
		arr3[temp][1]++;
	}
	for(int i = 0; i < 99; i++) {
		if(arr3[i][1] > highestDistribution)
			hDnum = i;
	}
	
	printf("The sum of all random numbers is: %d\n", sum);
	printf("The average of all random numbers is: %d\n", avg);
	printf("The highest distribution of numbers is: %d\n", hDnum);
	printf("Array 1:\n");
	printArr(arr);
	
	return 0;
}