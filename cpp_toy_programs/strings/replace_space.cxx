#include <iostream>
#include <string>
#include <cctype>
#include <cstring>
#include <cassert>

using namespace std;

void shift( char *str, int len, int nshift )
{
	for( int i = len+nshift-1; i>=nshift; --i )
		str[i] = str[i-nshift];
}

int space_count( char *str, int len )
{
	int count = 0;
	while( *str ) {
		if ( *str == ' ' ) ++count; 
		++str;
	}
	return count;
}

void replace_space( char *str, int len, int buf_len )
{
	// validate size
	int nspaces = space_count(str, len);
	assert( nspaces*2 + len <= buf_len );

	// repace spaces
	char sp[4] = "%20";
	for( int i = 0; i < len; ++i )
		if( str[i] == ' ' )
		{
			shift( &str[i], len - i, 2 );
			strncpy( &str[i], sp, 3 );
			i += 2;
			len += 2;
		}
	str[len] = 0;
}

int main()
{
	char input[1000];

	cout << "Enter a string: ";
	cin.getline(input, sizeof(input));

	replace_space( input, strlen(input), 1000 );

	cout << input << endl;

	return 0;
}
