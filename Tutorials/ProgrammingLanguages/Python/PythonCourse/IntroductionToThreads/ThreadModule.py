import thread

def gcd(a, b):
    """ Calculates gcd of two numbers"""
    if b > a: return gcd(b, a)
    if b == 0: return a
    return gcd(b, a%b)

threadComplete = 0
lock = thread.allocate_lock()
def printgcd(a, b):
    """ If you're lucky this will print neatly with all thread calls."""
    global threadComplete
    g = gcd(a,b)
    lock.acquire()
    print "GCD of %d and %d is %d" % ( a, b, g)
    print "Second print"
    threadComplete += 1
    lock.release()

def mainForThreads():
    thread.start_new_thread(printgcd, (12, 16))
    thread.start_new_thread(printgcd, (20, 16))
    thread.start_new_thread(printgcd, (8, 16))
    while threadComplete != 3:
        pass
    raw_input("Enter anything to exit...")

if __name__ == "__main__":
    mainForThreads()
