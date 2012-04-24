# Given a number n, give me a function that returns the nth fibonacci 
# number. Running time, space complexity, iterative vs. recursive.
import time
import copy

def recursionNoMemoNthFibo(n):
    if n==0: return 0
    elif n==1: return 1
    else: return recursionNoMemoNthFibo(n-1)+recursionNoMemoNthFibo(n-2)

def memoNthFibo(n, memo):
    if memo[n] >= 0: return memo[n]
    if n==0: memo[n] = 0
    elif n==1: memo[n] = 1
    else: memo[n] = memoNthFibo(n-1, memo) + memoNthFibo(n-2, memo)
    return memo[n]

def recursionMemoNthFibo(n):
    memo = [-1]*(n+1)
    return memoNthFibo(n, memo)

def iterativeNthFibo(n):
    if n==0: return 0
    elif n==1: return 1

    n_1 = 1
    n_2 = 0
    curN = 1
    res = 1
    while curN < n:
        res = n_1 + n_2
        curN += 1
        n_2 = n_1
        n_1 = res
    return res

class Matrix:
    def __init__(self, matrixData, rowSize, colSize):
        self.matrixData = matrixData
        self.rowSize = rowSize
        self.colSize = colSize

    def matrixMultiply(self, other):
        if self.colSize != other.rowSize:
            raise Exception("Cannot multiply! Column size of the first matrix "+
                            "and row size of the second matrix has to be same")
        resData = []
        for row in xrange(self.rowSize):
            temp = []
            for col in xrange(other.colSize):
                temp.append(0)
            resData.append(copy.deepcopy(temp))


        for row in xrange(self.rowSize):
            for col in xrange(other.colSize):
                for coltemp in xrange(self.colSize):
                    resData[row][col] += (self.matrixData[row][coltemp]*
                                      other.matrixData[coltemp][col])
        return Matrix(resData, self.rowSize, other.colSize)

    def exponentiate(self, n):
        if self.rowSize != self.colSize:
            raise Exception("Cannot Exponentiate! Row and column size of the " +
                            "matrix must match")

        if n == 0:
            raise Exception("Really? 0 for exponentiation?")
        if n == 1:
            return copy.deepcopy(self)
        elif n%2 == 0:
            res = self.exponentiate(n/2)
            
            return res.matrixMultiply(res) # x^(n/2) * x^(n/2)
        else:
            res = self.exponentiate((n-1)/2)
            res = res.matrixMultiply(res) # x^((n-1)/2) * x^((n-1)/2)
            
            return self.matrixMultiply(res) # x*x^(n-1)
                                    
def matrixExponentiationNthFibo(n):
    if n == 0: return 0
    if n == 1: return 1
    mulMatrixData = [[1, 1], [1,0]]
    mulMatrix = Matrix(mulMatrixData, 2, 2)
    mulMatrix = mulMatrix.exponentiate(n)
    f0f1 = [[0], [1]] # fibonacci(0) fibonacci(1)
    f0f1Matrix = Matrix(f0f1, 2, 1)
    res = mulMatrix.matrixMultiply(f0f1Matrix)
    return res.matrixData[0][0]

def timeTest(function, *args):
    print "Executing: " + function.__name__
    start = time.time()
    #print "Output: %d" %
    function(*args)
    print "Time taken: %.5f" % (time.time()-start)

def main():
    n = int(raw_input("Benchmark nth fibonacci number. Enter n please: "))
    #timeTest(recursionNoMemoNthFibo, n)
    #timeTest(recursionMemoNthFibo, n)
    timeTest(iterativeNthFibo, n)
    timeTest(matrixExponentiationNthFibo, n)

if __name__ == "__main__":
    main()
