#ifndef _COMBINATION_H_
#define _COMBINATION_H_

#include <string>
#include <vector>

using namespace std;

template < class ElemType, class ElemContainerType > 
	bool findCombinations(
		const ElemType &combineMe, 
		ElemContainerType &combinationList
		);

template <class ElemType, class ElemContainerType>
	bool findCombinations(
		const ElemType &combineMe,
		ElemContainerType &combinationList,
		ElemType &currentItem,
		int currentLoc
		);

template < class ElemType, class ElemContainerType > 
	bool findCombinations(
		const ElemType &combineMe, 
		ElemContainerType &combinationList
		)
{
	ElemType currentItem;
	return findCombinations(combineMe, combinationList, currentItem, 0);
}

template <class ElemType, class ElemContainerType>
	bool findCombinations(
		const ElemType &combineMe,
		ElemContainerType &combinationList,
		ElemType &currentItem,
		int startLoc
		)
{
	for(int currentLoc = startLoc; currentLoc < combineMe.size(); currentLoc++) 
	{
		// use the current item
		currentItem.push_back(combineMe[currentLoc]);
					
		// add it the combinations list
		combinationList.push_back(currentItem);

		// recurse to find more combinations 
		findCombinations(combineMe, combinationList, currentItem, currentLoc+1);
			
		// once used we should unuse it
		currentItem.erase(currentItem.size()-1);
	}
	return true;
}

#endif // _COMBINATION_H_

