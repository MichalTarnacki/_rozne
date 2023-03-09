from Core.Mode import ToStringMode


class Dimension:
    """Holds x and y dimension in one place"""

    def __init__(self, x: int, y: int):
        self.x = x
        self.y = y

    def __str__(self, mode: ToStringMode = ToStringMode.Pretty):
        if mode == ToStringMode.Pretty:
            return "[" + str(self.x) + ", " + str(self.y) + "]"
        else:
            return str(self.x) + " " + str(self.y)
