from node import Node
from graphviz import Graph

class AVL(object):

    __slots__ = ['root']

    def __init__(self):
        self.root = None 
    

    def search(self, k): 
        node = self.root

        while(True):
            if k == node.key:
                return True
            elif k < node.key:
                if node.left is None:
                    return False
                else:
                    node = node.left
            else:
                if node.right is None:  
                    return False
                else:
                    node = node.right
    

    def insert(self, k):
        new = Node(None, k)
        node = self.root
        if node is None:
            self.root = new
        else:
            while(True):
                if new.key < node.key:
                    if node.left is None:
                        new.parent = node
                        node.left = new
                        break
                    else:
                        node = node.left
                else:
                    if node.right is None:
                        new.parent = node
                        node.right = new
                        break
                    else:
                        node = node.right
            
        self.rebalance(new)

    
    def left_rotate(self, x):
        y = x.right
        y.parent = x.parent
        if y.parent is None:
            self.root = y
        else:
            if y.parent.left is x:
                y.parent.left = y
            elif y.parent.right is x:
                y.parent.right = y
        x.right = y.left
        if x.right is not None:
            x.right.parent = x
        y.left = x
        x.parent = y
        self.update_height(x)
        self.update_height(y)
    

    def right_rotate(self, x):
        y = x.left
        y.parent = x.parent
        if y.parent is None:
            self.root = y
        else:
            if y.parent.left is x:
                y.parent.left = y
            elif y.parent.right is x:
                y.parent.right = y
        x.left = y.right
        if x.left is not None:
            x.left.parent = x
        y.right = x
        x.parent = y
        self.update_height(x)
        self.update_height(y)
    

    def rebalance(self, node):
        while node is not None:
            self.update_height(node)
            if self.height(node.left) >= 2 + self.height(node.right):
                if self.height(node.left.left) >= self.height(node.left.right):
                    self.right_rotate(node)
                else:
                    self.left_rotate(node.left)
                    self.right_rotate(node)
            elif self.height(node.right) >= 2 + self.height(node.left):
                if self.height(node.right.right) >= self.height(node.right.left):
                    self.left_rotate(node)
                else:
                    self.right_rotate(node.right)
                    self.left_rotate(node)
            node = node.parent
    

    def delete(self, k):
        pass

    
    def printar(self, node):
        print('EU: ' + str(node.key))

        if node.left is not None:
            print('LEFT: ' + str(node.left.key))
        else:
            pass

        if node.right is not None:
            print('RIGHT: ' + str(node.right.key))
        else:
            pass
        
        if node.left is not None:
            self.printar(node.left)
        
        if node.right is not None:
            self.printar(node.right)

    
    def height(self, node):
        if node is None:
            return -1
        else:
            return node.height

    
    def update_height(self, node):
        node.height = max(self.height(node.left), self.height(node.right)) + 1