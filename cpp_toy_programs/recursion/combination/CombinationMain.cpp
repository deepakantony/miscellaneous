#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include "Combination.h"

using namespace std;

int main(int argc, char *argv[]) 
{
	if(argc != 2) 
	{
		cout << "Usage: " << argv[0] << " <combine_me_string>" << endl;
		return -1;
	}
	
	string combineMe(argv[1]);
	vector<string> combinationList;
	findCombinations(combineMe, combinationList);

	copy(
		combinationList.begin(), 
		combinationList.end(), 
		ostream_iterator<string>(cout, ",")
		);

	cout << endl;

	return 0;
}
