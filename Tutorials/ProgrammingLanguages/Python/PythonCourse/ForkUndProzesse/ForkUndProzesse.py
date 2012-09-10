import os

######### forking 

def childRun():
    print "A child: ", os.getpid()
    os._exit(0)

def parent():
    while True:
        newpid = os.fork()
        if newpid == 0:
            childRun()
        else:
            print "Parent: %d, child: %d" % (os.getpid(), newpid)
        if raw_input("Enter q to exit; any other key to continue: ") == 'q':
            break
        print

#########

######### exec*

def runTestExeclp():
    """ This should error out! """
    os.execlp("test.sh", "MY PROOF")
    
def runTestExeclpe():
    """ This should work; """
    # here you're replacing environment variable. uname will fail
    os.execlpe("test.sh", "MY PROOF", {"PATH":os.getcwd()})
    # here you're appending to PATH variable; comment above line
    os.execlpe("test.sh", "APPEND", {"PATH": os.environ["PATH"]+":"+os.getcwd()})
    # here I use a vector
    os.execvpe("test.sh", ["APPEND"], {"PATH": os.environ["PATH"]+":"+os.getcwd()})
    print "I SHOULD NEVER REACH THIS LINE"

#########

if __name__ == "__main__":
    runTestExeclpe()

