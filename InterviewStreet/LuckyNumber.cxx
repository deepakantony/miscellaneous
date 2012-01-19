#include <iostream>
#include <string>

using namespace std;

#define MAX_SUM_OF_SQUARES 1459 // (18 * 9 * 9) + 1

int primes[MAX_SUM_OF_SQUARES+1];

void initPrimes()
{
	primes[0] = primes[1] = 0;
	for(int index = 2; index <= MAX_SUM_OF_SQUARES; index++)
		primes[index] = -1;

	for(int index = 2; index <= MAX_SUM_OF_SQUARES; )
	{
		primes[index] = 1;
		int index2 = 2*index;
		while(index2 <= MAX_SUM_OF_SQUARES)
		{
			primes[index2] = 0;
			index2 += index;
		}

		while(index <= MAX_SUM_OF_SQUARES && primes[index] != -1)
			index++;
	}
}	

bool isPrime(int num)
{
	return (num <= MAX_SUM_OF_SQUARES && primes[num] == 1)?true:false;
}

class BigNum
{
public:
	BigNum(string num) {
		this->data = num;
	}

	BigNum& operator++() {
		
	}
	
	bool operator<=(const BigNum& num) const {
		
	}

	void sumAndSquareSum(int &sum, int &squareSum) {
		sum = 0;
		squareSum = 0;
		int dig;
		for(string::const_iterator it = num.begin();
			it != num.end(); it++)
		{
			dig = *it - '0';
			sum += dig;
			squareSum += dig*dig;
		}
	}
};

int main(int argc, char *argv[])
{
	initPrimes();
	int nTests;
	cin >> nTests;
	int A, B;
	int luckyNums = 0;
	int sum, squareSum;
	for(int index = 0; index < nTests; index++)
	{
		cin >> A;
		cin >> B;
		luckyNums = 0;
		for(int num = A; num <= B; num++) 
		{
			if(isPrime(num)) 
			{
				cout << num << endl;
				luckyNums++;
			}
		}

		cout << luckyNums << endl;
	}

	return 0;
}

