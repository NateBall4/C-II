#include <stdio.h> 
#include <iostream>
#include <conio.h>
#include <math.h> 

using namespace std;

#define OOB 0

void primeFactors(int);
int isPrime(int);

int main(){
	int num = 0;

	//gets input for the number
	cout << "please enter a number: ";
	cin >> num;

	//tests if the number is out of bounds
	if (num <= 1) {
		cout  << num << " is out of bounds" << endl;
		num = OOB;
	}

	//reprompts for input if number was OOB
	while (num == OOB) {
		cout << "please enter a number: ";
		cin >> num;

		if (num <= 1) {
			cout << num << " is out of bounds" << endl;
			num = OOB;
		}
	}

	//tests for prime or composite
	if (isPrime(num) == true) {
		cout << num << " is prime" << endl;
	}
	else {
		cout << num << " is Composite" << endl;
		_getch();
		//gets prime factors
		primeFactors(num);
	}

	_getch();
	return 0;
}

int isPrime(int amIPrime) {
	int i = 0;
	bool isPrime = true;

	// check for border cases
	if (amIPrime <= 1) {
		isPrime = false;
	}

	// force check the number for primality
	for (i = 2; i < amIPrime; i++) {
		if (amIPrime % i == 0)
			isPrime = false;
	}

	return isPrime;
}

void primeFactors(int n) {
	// Print the number of 2s that divide n 
	while (n % 2 == 0)
	{
		cout << "2 was found as a prime factor" << endl;
		n = n / 2;
	}

	// n must be odd at this point. 
	for (int i = 3; i <= sqrt(n); i = i + 2)
	{
		// While i divides n, print i and divide n 
		while (n%i == 0)
		{
			cout << i << " was found as a prime factor" << endl;
			n = n / i;
		}
	}

	// This condition is to handle the case when n  
	// is a prime number greater than 2 
	if (n > 2) {
		cout << n << " was found as a prime factor" << endl;
	}
}
