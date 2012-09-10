import os
import platform

if platform.system() == "Windows":
    import msvcrt

######### GETCH

def getch_with_system():
    """Runs os.system to prompt for a single key. Ignores the entered key."""
    if platform.system() == "Windows":
        msvcrt.getch()
    else:
        os.system("read -n 1")

def getch_with_popen():
    """ Runs popen to prompt for a single key. """
    if platform.system() == "Windows":
        msvcrt.getch()
    else:
        os.popen("read -n 1")
        
def mainForGetch():
    print "Type a key: "
    getch_with_system()
    print "Okay"

    print "Type another key: "
    getch_with_popen()
    print "Okay"


#########


######### execute command using 

def shellcommandUsingPopen(command):
    """ execute the command """ 
    handle = os.popen(command)
    for line in handle.readlines():
        print line.strip()

import subprocess
def shellcommandUsingSubprocess(command):
    """ execute the command using subprocess module. """
    process = subprocess.Popen(command, stdout=subprocess.PIPE)
    process.wait()
    print process.stdout.read()


def mainForShellCommand():
    command = raw_input("Enter your command: ")
    shellcommandUsingSubprocess(command)

#########

if __name__ == "__main__":
    mainForShellCommand()

