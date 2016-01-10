#include <iostream>
#include <array>

using namespace std;

bool is_similar( char *s1, char *s2 )
{
	array<int, 256> table;
	table.fill(0);

	for( char x : string(s1) ) table[x] += 1;

	for( char x : string(s2) ) table[x] -= 1;

	for( int x : table ) if ( x ) return false;

	return true;
}

int main()
{
	char s1[256], s2[256];
	cout << "Enter 2 strings: ";
	cin >> s1 >> s2;
	cout << is_similar(s1, s2);
	return 0;
}
