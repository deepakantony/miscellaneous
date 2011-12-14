#!python

# initial stub test
def printString(string):
    print string

# first non repeated char
def firstNonRepeatesChar(string):
    pass

# largest sum consecutive sequence
def largestSumConsecutiveSeq(aList, start, end):
    #TODO:error check for bounds
    

    # assume there is atleast one positive integer
    maxSum = [max(0,aList[start])]
    for index in xrange(start+1, end):
        maxSum.append(max(0, maxSum[index-1]+aList[index]))

    return max(maxSum)

    
