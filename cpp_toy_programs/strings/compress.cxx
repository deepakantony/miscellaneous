#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template<class IT, class T>
int consecutive_count( IT beg, IT end, T c )
{
	if ( beg == end ) return 0;

	int count = 0;
	do {
		++count;
		++beg;
	} while( beg != end && *beg == c );

	return count;
}

string compress( string &text )
{
	stringstream ss;
	for ( int i = 0; i < text.size(); )
	{
		int cc = consecutive_count(text.begin() + i, text.end(), text[i] );

		ss << text[i] << cc;

		i += cc;
	}

	if( text.size() > ss.str().size() ) return ss.str();
	else return text;
}

int main( int argc, char *argv[] )
{
	string text;

	cout << "Enter a string: ";
	cin >> text;
	cout << compress(text) << endl;
	return 0;
}
