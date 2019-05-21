class AVLNode(object):

    __slots__ = ['key', 'parent', 'left', 'right', 'height']

    def __init__(self, parent, key):
        self.key = key
        self.parent = parent
        self.left = None 
        self.right = None
        self.height = 0


class RBNode(object):

    __slots__ = ['key', 'color', 'left', 'right', 'parent']

    def __init__(key, color, parent):
        self.key = key
        self.parent = parent
        self.left = None 
        self.right = None
        self.color = color       