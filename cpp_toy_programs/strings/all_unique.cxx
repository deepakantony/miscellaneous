#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <bitset>

using namespace std;

template<typename T>
bool all_unique(const basic_string<T> &s)
{
	int a[(1 << (sizeof(T)*8))];
	memset( a, 0, sizeof(a));

	for( int i = 0; i < s.size(); ++i )
	{
		T x = s[i];
		
		if( isalpha(x) )
		{
			int index = x;
			a[index] += 1;

			if( a[index] > 1 ) {
				return false;
			}
		}
	}

	return true;
}

template<typename T>
bool all_unique2(const basic_string<T> &s)
{
	bitset<(1 << (sizeof(T)*8))> a;

	for( int i = 0; i < s.size(); ++i )
	{
		T x = s[i];
		
		if( isalpha(x) )
		{
			if( a.test((int)x) )
				return false;

			// else
			a.set((int)x);
		}
	}

	return true;
}

int main(int argc, char *argv[])
{
	string input;
	cout << "Enter a string: ";
	cin >> input;
	cout << all_unique2(input) << endl;
	return 0;
}


