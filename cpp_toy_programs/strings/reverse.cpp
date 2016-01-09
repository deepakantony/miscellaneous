#include <iostream>
#include <string>
#include <cstring>

using namespace std;

void swap( char &a, char &b)
{
	char temp = a;
	a = b;
	b = temp;
}

void reverse(char *str)
{
	int len = strlen(str);
	for( int i = 0, j = len - 1; i < j; ++i, --j )
		swap(str[i], str[j]);
}

int main( int argc, char *argv[] )
{
	char str[10000];
	cout << "Enter a string: ";
	cin >> str;
	reverse(str);
	cout << str << endl;
	return 0;
}
