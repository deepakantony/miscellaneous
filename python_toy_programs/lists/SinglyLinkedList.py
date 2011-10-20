# This module implements Singly Linked List

class SinglyLinkedListNode:
    def __init__(self, nodeData = None, nodeNext = None):
        self.next = nodeNext
        self.data = nodeData

class SinglyLinkedList:
    def __init__(self):
        self.start = None
        self.length = 0
    
    def insertFront(self, newNodeData):
        if not self.start:
            self.start = SinglyLinkedListNode(newNodeData)
        else:
            self.start = SinglyLinkedListNode(newNodeData, self.start)
        self.length += 1
        
    def insertEnd(self, newNodeData):
        if not self.start:
            self.start = SinglyLinkedListNode(newNodeData)
        else:
            lastNode = self.start
            while lastNode.next:
                lastNode = lastNode.next
            lastNode.next = SinglyLinkedListNode(newNodeData)
        self.length += 1

    def deleteNode(self, nodeValue):
        if not self.start:
            return False

        if start.data == nodeValue:
            self.deleteFront()
            return True

        prevNode = self.start
        delNode = self.start.next
        while delNode and delNode.data != nodeValue:
            prevNode = delNode
            delNode = delNode.next

        if delNode:
            prevNode.next = delNode.next
            del delNode
            self.length -= 1
            return True
        else:
            return False

    def deleteFront(self):
        if not self.start:
            return None
        delNode = self.start
        delNodeValue = delNode.data
        self.start = self.start.next
        del delNode
        self.length -= 1
        return delNodeValue

    def display(self):
        if not self.start:
            print "[]"
            return

        print "["
        tempNode = self.start
        while tempNode.next:
            print tempNode.data
            print ", "
        print tempNode.data
        print "]"

def main(args):
    print "Main is not implemented"

if __name__ == "__main__":
    import sys
    main(sys.args)


