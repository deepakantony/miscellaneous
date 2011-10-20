#include "Permute.h"
#include <bitset>

using namespace std;

// This is a recursive function to generate permutations. 
// Logic: 
void permute(
	string &currentPermutation,
	const string &permuteMe,
	vector<string> &permutationList,
	vector<bool> &usedPermutationList
	) 
{
	// if there are no more characters to permute, it means we have reached
	// the end of the permuteMe string. So add it to permutationList & return.
	if( currentPermutation.size() >= permuteMe.size() )
	{
		permutationList.push_back(currentPermutation);
		return;
	}

	// Iterate from start index till the end of permuteMe string and 
	// recursively permute it.
	for(int permuteMeIndex = 0; 
		permuteMeIndex < permuteMe.size();
		permuteMeIndex++
		)
	{
		// Cannot use a character if its already been used 
		if(usedPermutationList[permuteMeIndex])
			continue;
		
		currentPermutation.push_back(permuteMe[permuteMeIndex]);
		usedPermutationList[permuteMeIndex] = true;
		permute(
			currentPermutation, permuteMe, 
			permutationList, usedPermutationList 
			);
			
		currentPermutation.erase(currentPermutation.size()-1);
		usedPermutationList[permuteMeIndex] = false;
	}
}

// This is the api function
// This will call the appropriate function required
void permute(const string permuteMe, vector<string> &permutationList)
{
	string currentPermutation;
	vector<bool> usedPermutationList(permuteMe.size(), false);
	permute(
		currentPermutation,
		permuteMe,
		permutationList,
		usedPermutationList
		);
}
