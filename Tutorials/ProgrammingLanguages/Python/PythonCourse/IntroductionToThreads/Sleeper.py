import time
from threading import Thread, Lock

lck = Lock()
def sleeper(index):
    """ This function just sleeps for 5 seconds """
    print "Thread %d sleeps for 5 seconds" % index
    time.sleep(5)
    lck.acquire()
    print "Thread %d woke up" %index
    lck.release()

def main():
    for i in xrange(10):
        t = Thread(target=sleeper, args=(i,))
        t.start()

if __name__ == "__main__":
    main()
