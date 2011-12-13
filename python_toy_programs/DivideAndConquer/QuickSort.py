#!python

def swapListIndex(aList, index1, index2):
    temp = aList[index1]
    aList[index1] = aList[index2]
    aList[index2] = temp

def quickSort(aList, start, end):
    if start >= end:
        return
    
    startIndex = start + 1
    endIndex = end
    
    while startIndex <= endIndex:
        while startIndex <= endIndex and aList[startIndex] <= aList[start]:
            startIndex += 1
        while startIndex <= endIndex and aList[endIndex] > aList[start]:
            endIndex -= 1
        if startIndex < endIndex:
            swapListIndex(aList, startIndex, endIndex)

    swapListIndex(aList, endIndex, start)
    quickSort(aList, start, endIndex-1)
    quickSort(aList, endIndex+1, end)

def main():
    l = [1,2,3,4,10,10,2,3,4,5,98,434,3,45,2, 3,4,23,342,3]
    print l
    quickSort(l, 0, len(l)-1)
    print l

if __name__ == "__main__":
    main()
            

