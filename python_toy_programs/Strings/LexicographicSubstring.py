#!/usr/bin/env python

# Problem originally found @ 
# http://www.interviewstreet.com/recruit/challenges/solve/view/4e1491425cf10/4efa210eb70ac
#
# Find Strings (25 points)
# You are given 'n' strings w1, w2, ......, wn. Let Si denote the set of strings
# formed by considering all unique substrings of the string wi. A substring is 
# defined as a contiguous sequence of one or more characters in the string. 
# More information on substrings can be found here. Let 'S' = {S1 U S2 U .... Sn}
# .i.e 'S' is a set of strings formed by considering all the unique strings in 
# all sets S1, S2, ..... Sn. You will be given many queries and for each query, 
# you will be given an integer 'k'. Your task is to output the lexicographically 
# kth smallest string from the set 'S'.
#  
# Input:
# The first line of input contains a single integer 'n', denoting the number of 
# strings. Each of the next 'n' lines consists of a string. The string on the 
# ith line (1<=i<=n) is denoted by wi and has a length mi. The next line consists 
# of a single integer 'q', denoting the number of queries. Each of the next 'q' 
# lines consists of a single integer 'k'.
# Note: The input strings consist only of lowercase english alphabets 'a' - 'z'.
#  
# Output:
# Output 'q' lines, where the ith line consists of a string which is the answer 
# to the ith query. If the input is invalid ('k' > |S|), output "INVALID" 
# (quotes for clarity) for that case.
# 
# Constraints:
# 1<=n<=50
# 1<=mi<=2000
# 1<=q<=500
# 1<=k<=1000000000
# 
# Sample Input:
# 2
# aab
# aac
# 3
# 3
# 8
# 23
# 
# Sample Output:
# aab
# c
# INVALID
# 
# Explanation:
# For the sample test case, we have 2 strings "aab" and "aac".
# S1 = {"a", "aa", "aab", "ab", "b"} . These are the 5 unique substrings of "aab".
# S2 = {"a", "aa", "aac",  "ac", "c" } . These are the 5 unique substrings of "aac".
# Now, S = {S1 U S2} = {"a", "aa", "aab", "aac", "ab", "ac", "b", "c"}. Totally, 
# 8 unique strings are present in the set 'S'. 
# The lexicographically 3rd smallest string in 'S' is "aab" and the 
# lexicographically 8th smallest string in 'S' is "c". Since there are only 8 
# distinct substrings, the answer to the last query is "INVALID".
# 

import sys
import time

# This function will create a set of all the substrings for a given string
def setOfSubstrings(inStr, subStrSet):
    print inStr
    inStrLen = len(inStr)
    for i in xrange(inStrLen):
        for j in xrange(i, inStrLen):
            subStrSet.add(inStr[i:j+1])
           
# The above function is not memory efficient; lets try something different
def lexicallySortedItem():
    pass

# The following main is a memory optimized
def main(argv):
    start = time.time()
    inp = sys.stdin
    out = sys.stdout
    if len(argv) > 1:
        try:
            inp = open(argv[1], 'r')
            if len(argv) > 2:
                out = open(argv[2], 'w')
        except IOError as err:
            print err

    # First get the number of strings
    nStrings = int(inp.readline())
    # Then the strings
    strings = []
    for x in xrange(nStrings):
        curStr = inp.readline().rstrip()
        strings.append(curStr)

    # queries
    nQueries = int(inp.readline())
    queries = []
    for x in xrange(nQueries):
        queries.append(int(inp.readline()))
    sortedQueries = list(queries)
    
    print "Total Executaion time %f secs" % (time.time()-start)

# Main function
def main_non_memory(argv):
    inp = sys.stdin
    out = sys.stdout
    if len(argv) > 1:
        try:
            inp = open(argv[1], 'r')
            if len(argv) > 2:
                out = open(argv[2], 'w')
        except IOError as err:
            print err

    # First get the number of strings
    nStrings = int(inp.readline())
    # Then the strings
    subStrings = set([])
    for x in xrange(nStrings):
        curStr = inp.readline().rstrip()
        setOfSubstrings(curStr, subStrings)

    # Lexically sort the list of all substrings
    subStringList = list(subStrings)
    subStringList.sort()
    subStringListLen = len(subStringList)        

    # queries
    nQueries = int(inp.readline())
    for x in xrange(nQueries):
        curQuery = int(inp.readline())
        
        if curQuery > subStringListLen:
            print >> out, "INVALID"
        else:
            print >> out, subStringList[curQuery - 1]

if __name__ == "__main__":
    main(sys.argv)
