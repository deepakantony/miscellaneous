#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool isrotation( const string &s1, const string &s2 )
{
	if( s1.size() != s2.size() )
		return false;

	string s1s1 = s1 + s1;

	return search(s1s1.begin(), s1s1.end(), s2.begin(), s2.end()) != s1s1.end();
}

int main()
{
	string s1,s2;
	cout << "Enter 2 strings: ";
	cin >> s1 >> s2;
	cout << "Is rotation: " << isrotation(s1,s2) << endl;
	return 0;
}
