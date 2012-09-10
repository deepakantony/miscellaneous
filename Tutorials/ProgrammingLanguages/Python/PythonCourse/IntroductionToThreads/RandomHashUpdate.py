import threading

class HashClass(threading.Thread):
    hashObj = {}
    lck = threading.Lock()
    def __init__(self):
        threading.Thread.__init__(self)

    def run(self):
        for index in xrange(100):
            HashClass.lck.acquire()
            if index not in HashClass.hashObj:
                HashClass.hashObj[index] = 1
            else:
                HashClass.hashObj[index] += 1
            HashClass.lck.release()


def main():
    allThreads = []
    totalThreads = 1000
    for thread in xrange(totalThreads):
        t = HashClass()
        allThreads.append(t)
        t.start()

    for t in allThreads:
        t.join()
            
    for (key, value) in HashClass.hashObj.iteritems():
        if value != totalThreads:
            print key, value
            print "done"
                    
if __name__ == "__main__":
    main()

