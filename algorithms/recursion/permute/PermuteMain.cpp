#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include "Permute.h"

using namespace std;

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		cout << "Usage: " << argv[0] << " <permuteMeString> " << endl;
		return -1;
	}

	string permuteMe(argv[1]);
	vector<string> permutationList;
	permute(permuteMe, permutationList);

	copy(
		permutationList.begin(), permutationList.end(),
		ostream_iterator<string>(cout, "\n")
		);

	return 0;
}
