import sys

def nOfTriminoes(mBoardSize):
    if mBoardSize == 1:
        return 0
    elif mBoardSize == 2:
        return 1
    else:
        return 1 + 4*nOfTriminoes(mBoardSize/2) 

def main(argv):
    if len(argv) != 2:
        print "Usage: " + argv[0] + " <board size power of 2>"
        return -1

    if (int(argv[1]) <= 0) or (int(argv[1]) & (int(argv[1])-1)) != 0:
        print "Board sides should be 2^n"
        return -1

    print "Number of triminoes: " + repr(nOfTriminoes(int(argv[1])))

    return 0

if __name__ == "__main__":
   main(sys.argv)





