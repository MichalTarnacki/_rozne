from Core.Mode import ToStringMode


class Location:
    """Holds location"""

    def __init__(self, x: int = None, y: int = None):
        if x is not None:
            self.x = x
        else:
            self.x = -1
        if y is not None:
            self.y = y
        else:
            self.y = -1

    def __str__(self, mode: ToStringMode = ToStringMode.Pretty):
        if mode == ToStringMode.Pretty:
            return "(" + str(self.x) + ", " + str(self.y) + ")"
        else:
            return str(self.x) + " " + str(self.y)

    def get_x(self):
        return self.x

    def get_y(self):
        return self.y

    def set(self, x: int, y: int):
        self.x = x
        self.y = y

    def __eq__(self, other):
        if isinstance(other, self.__class__):
            if other.x == self.x and other.y == self.y:
                return True
        return False

    def __ne__(self, other):
        if self == other:
            return False
        return True
